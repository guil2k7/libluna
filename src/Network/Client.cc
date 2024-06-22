// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include "spdlog/spdlog.h"
#include <Luna/Network/Client.hh>
#include <Luna/Network/Auth.hh>
#include <Luna/Network/Code/Core.hh>
#include <Luna/BitSerde.hh>
#include <RakNet/RakNetworkFactory.h>
#include <RakNet/PacketEnumerations.h>
#include <RakNet/MTUSize.h>

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

bool CClient::SetConnectData(CConnectData const& data) {
    if (m_State != CLIENT_STATE_DISCONNECTED)
        return false;

    m_ConnectData = data;

    return true;
}

void CClient::Connect() {
    m_RakPeer->Disconnect(100);
    m_RakPeer->Initialize(1, 0, 30);

    m_RakPeer->Connect(m_ConnectData.Host.data(), m_ConnectData.Port, nullptr, 0);
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

void CClient::SendPacket(IPacketSerializable& packet, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
    uint8_t buffer[MAXIMUM_MTU_SIZE];
    CSerializer serializer(buffer, MAXIMUM_MTU_SIZE);

    if (packet.IsRPC()) {
        serializer.SerializeObject(packet);

        m_RakPeer->RPC(
            packet.ID(),
            reinterpret_cast<char const*>(buffer),
            serializer.OffsetInBits(),
            priority, reliability,
            0, RakNet::UNASSIGNED_PLAYER_ID, false, false
        );
    }
    else {
        serializer.SerializeU8(packet.ID());
        serializer.SerializeObject(packet);

        m_RakPeer->Send(
            reinterpret_cast<char const*>(buffer),
            serializer.OffsetInBytes(),
            priority, reliability,
            0, RakNet::UNASSIGNED_PLAYER_ID, false
        );
    }
}

void CClient::ProcessPreConnection(RakNet::Packet* packet) {
    switch (packet->data[0]) {
    case RakNet::ID_AUTH_KEY:
        spdlog::info("ID_AUTH_KEY");
        ProcessAuthRequest(packet);
        break;

    case RakNet::ID_CONNECTION_REQUEST_ACCEPTED:
        spdlog::info("ID_CONNECTION_REQUEST_ACCEPTED");
        ProcessConnectionRequestAccepted(packet);
        break;

    case RakNet::ID_CONNECTION_ATTEMPT_FAILED:
        spdlog::info("Connection attempt failed. Retrying...");
        Connect();
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

void CClient::ProcessAuthRequest(RakNet::Packet* packet) {
    CDeserializer deserializer(packet->data + 1, BitsToBytes(packet->bitSize));

    Code::CAuthRequest request;
    deserializer.DeserializeObject(request);

    Code::CAuthResponse response;
    response.auth = GenerateAuthKey(request.auth);

    SendPacket(response, RakNet::SYSTEM_PRIORITY, RakNet::RELIABLE);
}

void CClient::ProcessConnectionRequestAccepted(RakNet::Packet* packet) {
    m_State = CLIENT_STATE_CONNECTED;

    CDeserializer deserializer(packet->data + 1, BitsToBytes(packet->bitSize));

    Code::CConnectionRequestAccepted data;
    deserializer.DeserializeObject(data);

    Code::CClientJoin response;
    response.Version = 4057;
    response.Mod = 1;
    response.Nickname = m_ConnectData.Nickname;
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
