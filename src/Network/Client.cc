// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Network/Client.hh>
#include <Luna/Network/Code/Core.hh>
#include <Luna/Serde/BitSerde.hh>
#include <RakNet/RakNetworkFactory.h>
#include <RakNet/BitStream.h>
#include <RakNet/PacketEnumerations.h>
#include <RakNet/MTUSize.h>
#include <spdlog/spdlog.h>
#include <malloc.h>

using namespace Luna;
using namespace Luna::Network;
using namespace Luna::Serde;

#define CLIENT_VERSION_LEGACY_037 4057
#define CLIENT_VERSION_LEGACY_03DL 4062

CClient* Network::client = nullptr;

static inline CBitDeserializer CreateDeserializerFromPacket(RakNet::Packet const* packet) {
    return CBitDeserializer(packet->data + 1, packet->bitSize - 8);
}

CClient::CClient() {
    static_assert(sizeof (RakNet::RPCID) == 1);

    m_RakPeer = RakNet::RakNetworkFactory::GetRakPeerInterface();
    m_State = CLIENT_STATE_DISCONNECTED;
    m_RpcHandlers = new CRpcEventHandler[256];
}

CClient::~CClient() {
    RakNet::RakNetworkFactory::DestroyRakPeerInterface(m_RakPeer);

    delete[] m_RpcHandlers;
}

bool CClient::SetConnectionParams(CConnectionParams const& params) {
    if (m_State != CLIENT_STATE_DISCONNECTED)
        return false;

    m_ConnectionParams = params;

    return true;
}

void CClient::Connect() {
    m_RakPeer->Disconnect(100);
    m_RakPeer->Initialize(1, 0, 30);
    m_RakPeer->Connect(m_ConnectionParams.Host.data(), m_ConnectionParams.Port, nullptr, 0);

    m_ServerAddr = m_RakPeer->GetServerID();
    m_State = CLIENT_STATE_CONNECTING;
}

void CClient::Process() {
    if (m_State == CLIENT_STATE_DISCONNECTED)
        return;

    RakNet::Packet* packet = m_RakPeer->Receive();

    while (packet != nullptr) {
        try {
            ProcessPacket(packet);
        }
        catch (std::exception& exception) {
            spdlog::info("An exception occurred while processing a packet (ID: {}): {}", packet->data[0], exception.what());
        }

        m_RakPeer->DeallocatePacket(packet);
        packet = m_RakPeer->Receive();
    }
}

bool CClient::SendPacket(PacketID id, ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
    uint8_t buffer[MAXIMUM_MTU_SIZE];

    Serde::CBitSerializer serializer(&buffer[0], MAXIMUM_MTU_SIZE);

    try {
        serializer.SerializeU8(id);
        serializer.SerializeObject(data);
    }
    catch (CSerdeException& exception) {
        spdlog::info("{}", exception.what());
    }

    return m_RakPeer->Send(
        reinterpret_cast<char const*>(buffer),
        serializer.OffsetInBytes(),
        priority, reliability,
        0, m_ServerAddr, false
    );
}

bool CClient::SendRPC(PacketID id, ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
    uint8_t buffer[MAXIMUM_MTU_SIZE];

    CBitSerializer serializer(&buffer[0], MAXIMUM_MTU_SIZE);

    try {
        serializer.SerializeObject(data);
    }
    catch (CSerdeException& exception) {
        spdlog::info("{}", exception.what());
    }

    return m_RakPeer->RPC(
        id,
        reinterpret_cast<char const*>(buffer),
        serializer.OffsetInBits(),
        priority, reliability,
        0, m_ServerAddr, false, false
    );
}

bool CClient::RegisterHandlerForRPC(RakNet::RPCID id, CRpcEventHandler handler) {
    if (m_RpcHandlers[id].Callback != nullptr)
        return false;

    m_RpcHandlers[id].Callback = handler.Callback;
    m_RpcHandlers[id].UserData = handler.UserData;

    return true;
}

void CClient::RetryConnect() {
    m_RakPeer->Connect(m_ConnectionParams.Host.data(), m_ConnectionParams.Port, nullptr, 0);
    m_State = CLIENT_STATE_CONNECTING;
}

void CClient::ProcessPacket(RakNet::Packet const* packet) {
    bool isRPC = packet->data[0];

    if (isRPC) {
        ProcessRPC(packet);
        return;
    }

    for (auto handler : m_PacketHandlers) {
        if (handler->OnReceivePacket(
            *this,
            packet->data[0],
            packet->data + 1,
            packet->bitSize - 8
        )) {
            break;
        }
    }

    switch (packet->data[0]) {
    case RakNet::ID_CONNECTION_REQUEST_ACCEPTED:
        ProcessConnectionRequestAccepted(packet);
        break;

    case RakNet::ID_CONNECTION_ATTEMPT_FAILED:
        spdlog::info("Connection attempt failed. Retrying...");
        RetryConnect();
        break;

    case RakNet::ID_CONNECTION_LOST:
    case RakNet::ID_DISCONNECTION_NOTIFICATION:
        m_State = CLIENT_STATE_DISCONNECTED;
        break;
    }
}

void CClient::ProcessConnectionRequestAccepted(RakNet::Packet const* packet) {
    auto deserializer = CreateDeserializerFromPacket(packet);

    Code::CConnectionRequestAccepted data;
    deserializer.DeserializeObject(data);

    Code::CClientLogin response;
    response.ClientVersion = CLIENT_VERSION_LEGACY_037;
    response.Modded = 1;
    response.Nickname = m_ConnectionParams.Nickname;
    response.ClientChallengeResponse = data.SampToken ^ CLIENT_VERSION_LEGACY_037;
    response.Auth = "15121F6F18550C00AC4B4F8A167D0379BB0ACA99043";
    response.ClientVersionString = "0.3.7";

    Send(response, RakNet::HIGH_PRIORITY, RakNet::RELIABLE);

    m_State = CLIENT_STATE_CONNECTED;
    m_OurID = data.PlayerIndex;
}

void CClient::ProcessRPC(RakNet::Packet const* packet) {
    RakNet::BitStream bitStream(packet->data, BitsToBytes(packet->bitSize), false);

    RakNet::RPCID rpcID;
    uint32_t dataSizeInBits;
    uint8_t* data;

    bitStream.IgnoreBits(8);
    bitStream.Read<RakNet::RPCID>(rpcID);
    bitStream.ReadCompressed<uint32_t>(dataSizeInBits);

    if (bitStream.GetReadOffset() % 8 == 0) {
        data = packet->data + BitsToBytes(bitStream.GetReadOffset());
    }
    else {
        // We have to copy into a new data chunk because
        // the user data is not byte aligned.
        data = reinterpret_cast<uint8_t*>( alloca(BitsToBytes(dataSizeInBits)) );
        bitStream.ReadBits(data, dataSizeInBits);
    }

    if (m_RpcHandlers[rpcID].Callback != nullptr) {
        try {
            m_RpcHandlers[rpcID].Callback(
                m_RpcHandlers[rpcID].UserData, *this, data, dataSizeInBits);
        }
        catch (std::exception& exception) {
            spdlog::info("An exception occurred while processing a RPC (ID: {}): {}", rpcID, exception.what());
        }
    }
    else {
        spdlog::info("No RPC handler found for ID: {}.", rpcID);
    }
}
