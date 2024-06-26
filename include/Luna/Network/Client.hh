// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Packet.hh"
#include "../Serde/Serde.hh"
#include <RakNet/RakPeerInterface.h>
#include <string>

namespace Luna::Network {
    class CClient;

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

    struct IPacketEventHandler {
        /// Returns true to prevent others handlers from receiving a notification for this packet.
        virtual bool OnReceivePacket(CClient& client, PacketID id, uint8_t const* data, size_t bitSize) = 0;
    };

    typedef void (*RpcEventHandlerCallback)(void* userData, CClient& client, uint8_t const* data, size_t bitSize);

    struct CRpcEventHandler {
        constexpr CRpcEventHandler() : Callback(nullptr), UserData(nullptr) {}

        CRpcEventHandler(void* userData, RpcEventHandlerCallback callback) :
            UserData(userData), Callback(callback) {}

        void* UserData;
        RpcEventHandlerCallback Callback;
    };

    class CClient {
    public:
        CClient();
        ~CClient();

        bool SetConnectionParams(CConnectionParams const& params);
        void Connect();
        void Process();

        bool SendPacket(PacketID id, Serde::ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability);
        bool SendRPC(PacketID id, Serde::ISerializable const& data, RakNet::PacketPriority priority, RakNet::PacketReliability reliability);

        template<typename T>
        inline bool Send(T const& packet, RakNet::PacketPriority priority, RakNet::PacketReliability reliability) {
            if constexpr (IsRPC<T>()) {
                return SendRPC(GetPacketID<T>(), packet, priority, reliability);
            }
            else {
                return SendPacket(GetPacketID<T>(), packet, priority, reliability);
            }
        }

        bool RegisterHandlerForRPC(RakNet::RPCID id, CRpcEventHandler handler);

        inline void RegisterPacketHandler(IPacketEventHandler* handler) {
            m_PacketHandlers.push_back(handler);
        }

        inline eClientState State() const {
            return m_State;
        }

        inline uint16_t OurID() const {
            return m_OurID;
        }

    private:
        void RetryConnect();
        void ProcessPacket(RakNet::Packet const* packet);
        void ProcessConnectionRequestAccepted(RakNet::Packet const* packet);
        void ProcessRPC(RakNet::Packet const* packet);

        RakNet::RakPeerInterface* m_RakPeer;
        RakNet::PlayerID m_ServerAddr;
        eClientState m_State;
        CConnectionParams m_ConnectionParams;
        uint16_t m_OurID;

        CRpcEventHandler* m_RpcHandlers;
        std::vector<IPacketEventHandler*> m_PacketHandlers;
    };

    extern CClient* client;
}
