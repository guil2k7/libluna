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

    class CClient {
    public:
        CClient();
        ~CClient();

        void Connect(std::string_view host, int port);
        void Process();

        inline eClientState State() const {
            return m_State;
        }

        void SendPacket(IPacketSerializable& packet, RakNet::PacketPriority priority, RakNet::PacketReliability reliability);

        std::string Nickname;

    private:
        void ProcessPreConnection(RakNet::Packet* packet);
        void ProcessPostConnection(RakNet::Packet* packet);
        void ProcessAuthRequest(RakNet::Packet* packet);
        void ProcessConnectionRequestAccepted(RakNet::Packet* packet);
        void ProcessRPC(RakNet::Packet* packet);

        RakNet::RakPeerInterface* m_RakPeer;
        eClientState m_State;
    };

    extern CClient* client;
}
