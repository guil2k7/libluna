// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Packet.hh"
#include <RakNet/RakPeerInterface.h>
#include <string>

namespace Luna::Network {
    enum eClientState {
        CLIENT_STATE_UNDEFINED,
        CLIENT_STATE_DISCONNECTED,
        CLIENT_STATE_CONNECTED,
        CLIENT_STATE_CONNECTING,
    };

    struct CConnectData {
        std::string Host;
        uint16_t Port;
        std::string Nickname;
    };

    class CClient {
    public:
        CClient();
        ~CClient();

        bool SetConnectData(CConnectData const& data);
        void Connect();
        void Process();

        inline eClientState State() const {
            return m_State;
        }

        void SendPacket(IPacketSerializable& packet, RakNet::PacketPriority priority, RakNet::PacketReliability reliability);

    private:
        void ProcessPreConnection(RakNet::Packet* packet);
        void ProcessPostConnection(RakNet::Packet* packet);
        void ProcessAuthRequest(RakNet::Packet* packet);
        void ProcessConnectionRequestAccepted(RakNet::Packet* packet);
        void ProcessRPC(RakNet::Packet* packet);

        RakNet::RakPeerInterface* m_RakPeer;
        eClientState m_State;
        CConnectData m_ConnectData;
    };

    extern CClient* client;
}
