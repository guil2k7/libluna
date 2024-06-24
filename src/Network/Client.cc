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

#define CLIENT_VERSION_LEGACY_037 4057
#define CLIENT_VERSION_LEGACY_03DL 4062

CClient* Network::client = nullptr;

static inline CDeserializer CreateDeserializerFromPacket(RakNet::Packet* packet) {
    return CDeserializer(packet->data + 1, packet->bitSize - 8);
}

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
        if (m_State != CLIENT_STATE_CONNECTED)
            ProcessPreConnection(packet);
        else
            ProcessPostConnection(packet);

        m_RakPeer->DeallocatePacket(packet);
        packet = m_RakPeer->Receive();
    }
}

bool CClient::SendPacket(PacketID id, BitSerde::ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
    uint8_t buffer[MAXIMUM_MTU_SIZE];

    CSerializer serializer(&buffer[0], MAXIMUM_MTU_SIZE);
    serializer.SerializeU8(id);
    serializer.SerializeObject(data);

    return m_RakPeer->Send(
        reinterpret_cast<char const*>(buffer),
        serializer.OffsetInBytes(),
        priority, reliability,
        0, m_ServerAddr, false
    );
}

bool CClient::SendRPC(PacketID id, BitSerde::ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
    uint8_t buffer[MAXIMUM_MTU_SIZE];

    CSerializer serializer(&buffer[0], MAXIMUM_MTU_SIZE);
    serializer.SerializeObject(data);

    return m_RakPeer->RPC(
        id,
        reinterpret_cast<char const*>(buffer),
        serializer.OffsetInBits(),
        priority, reliability,
        0, m_ServerAddr, false, false
    );
}

void CClient::RetryConnect() {
    m_RakPeer->Connect(m_ConnectionParams.Host.data(), m_ConnectionParams.Port, nullptr, 0);
    m_State = CLIENT_STATE_CONNECTING;
}

void CClient::ProcessPreConnection(RakNet::Packet* packet) {
    switch (packet->data[0]) {
    case RakNet::ID_CONNECTION_REQUEST_ACCEPTED:
        ProcessConnectionRequestAccepted(packet);
        break;

    case RakNet::ID_CONNECTION_ATTEMPT_FAILED:
        spdlog::info("Connection attempt failed. Retrying...");
        RetryConnect();
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
    CDeserializer deserializer = CreateDeserializerFromPacket(packet);

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
}

void CClient::ProcessRPC(RakNet::Packet* packet) {
    // TODO: Implement
}
