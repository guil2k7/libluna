// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Network/Client.hh>
#include <Luna/Network/Code/Core.hh>
#include <Luna/BitSerde.hh>
#include <RakNet/RakNetworkFactory.h>
#include <RakNet/PacketEnumerations.h>
#include <RakNet/MTUSize.h>
#include <spdlog/spdlog.h>

using namespace Luna;
using namespace Luna::Network;
using namespace Luna::BitSerde;

CClient* Network::client = nullptr;

CClient::CClient() {
    m_RakPeer = RakNet::RakNetworkFactory::GetRakPeerInterface();
    m_State = CLIENT_STATE_DISCONNECTED;
}

CClient::~CClient() {
    RakNet::RakNetworkFactory::DestroyRakPeerInterface(m_RakPeer);
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
        spdlog::info("Processing packet: {}", packet->data[0]);

        if (m_State != CLIENT_STATE_CONNECTED)
            ProcessPreConnection(packet);
        else
            ProcessPostConnection(packet);

        m_RakPeer->DeallocatePacket(packet);
        packet = m_RakPeer->Receive();
    }
}

void CClient::SendPacket(IPacketSerializable const& packet, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
    uint8_t buffer[MAXIMUM_MTU_SIZE];
    CSerializer serializer(&buffer[0], MAXIMUM_MTU_SIZE);

    if (packet.IsRPC()) {
        serializer.SerializeObject(packet);

        m_RakPeer->RPC(
            packet.ID(),
            reinterpret_cast<char const*>(buffer),
            serializer.OffsetInBits(),
            priority, reliability,
            0, m_ServerAddr, false, false
        );
    }
    else {
        serializer.SerializeU8(packet.ID());
        serializer.SerializeObject(packet);

        m_RakPeer->Send(
            reinterpret_cast<char const*>(buffer),
            serializer.OffsetInBytes(),
            priority, reliability,
            0, m_ServerAddr, false
        );
    }
}

void CClient::RetryConnect() {
    m_RakPeer->Connect(m_ConnectionParams.Host.data(), m_ConnectionParams.Port, nullptr, 0);
    m_State = CLIENT_STATE_CONNECTING;
}

void CClient::ProcessPreConnection(RakNet::Packet* packet) {
    switch (packet->data[0]) {
    case RakNet::ID_AUTH_KEY:
        // Unrechable
        spdlog::info("ID_AUTH_KEY");
        break;

    case RakNet::ID_CONNECTION_REQUEST_ACCEPTED:
        spdlog::info("ID_CONNECTION_REQUEST_ACCEPTED");
        ProcessConnectionRequestAccepted(packet);
        break;

    case RakNet::ID_CONNECTION_ATTEMPT_FAILED:
        spdlog::info("Connection attempt failed. Retrying...");
        RetryConnect();
        break;

    case RakNet::ID_RPC:
        spdlog::info("Processing RPC: {}", packet->data[1]);
        ProcessRPC(packet);
        break;

    case RakNet::ID_MODIFIED_PACKET:
        spdlog::info("ID_MODIFIED_PACKET");
        break;
    }
}

void CClient::ProcessPostConnection(RakNet::Packet* packet) {
    switch (packet->data[0]) {
    case RakNet::ID_RPC:
        ProcessRPC(packet);
        break;

    case RakNet::ID_CONNECTION_LOST:
    case RakNet::ID_DISCONNECTION_NOTIFICATION:
        m_State = CLIENT_STATE_DISCONNECTED;
        break;
    }
}

void CClient::ProcessConnectionRequestAccepted(RakNet::Packet* packet) {
    m_State = CLIENT_STATE_CONNECTED;

    CDeserializer deserializer(packet->data + 1, BitsToBytes(packet->bitSize));

    Code::CConnectionRequestAccepted data;
    deserializer.DeserializeObject(data);

    Code::CClientJoin response;
    response.Version = 4057;
    response.Mod = 1;
    response.Nickname = m_ConnectionParams.Nickname;
    response.ClientChallengeResponse = data.SampToken ^ 4057;
    response.Auth = "15121F6F18550C00AC4B4F8A167D0379BB0ACA99043";
    response.ClientVersion = "0.3.7";

    SendPacket(response, RakNet::HIGH_PRIORITY, RakNet::RELIABLE);
}

void CClient::ProcessRPC(RakNet::Packet* packet) {
    if (packet->data[1] == 139) {
        spdlog::info("CInitGame");
    }
}
