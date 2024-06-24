// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Packet.hh"
#include "../BitSerde.hh"
#include <RakNet/RakPeerInterface.h>
#include <string>

namespace Luna::Network {
    enum eClientState {
        CLIENT_STATE_UNDEFINED,
        CLIENT_STATE_DISCONNECTED,
        CLIENT_STATE_CONNECTED,
        CLIENT_STATE_CONNECTING,
    };

    struct CConnectionParams {
        std::string Nickname;
        std::string Host;
        uint16_t Port;
    };

    class CClient {
    public:
        CClient();
        ~CClient();

        bool SetConnectionParams(CConnectionParams const& params);
        void Connect();
        void Process();

        inline eClientState State() const {
            return m_State;
        }

        bool SendPacket(PacketID id, BitSerde::ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability);
        bool SendRPC(PacketID id, BitSerde::ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability);

        template<typename T>
        inline bool Send(T const& packet, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
            if constexpr (IsRPC<T>()) {
                return SendRPC(GetPacketID<T>(), packet, priority, reliability);
            }
            else {
                return SendPacket(GetPacketID<T>(), packet, priority, reliability);
            }
        }

    private:
        void RetryConnect();
        void ProcessPreConnection(RakNet::Packet* packet);
        void ProcessPostConnection(RakNet::Packet* packet);
        void ProcessConnectionRequestAccepted(RakNet::Packet* packet);
        void ProcessRPC(RakNet::Packet* packet);

        RakNet::RakPeerInterface* m_RakPeer;
        RakNet::PlayerID m_ServerAddr;
        eClientState m_State;
        CConnectionParams m_ConnectionParams;
    };

    extern CClient* client;
}
