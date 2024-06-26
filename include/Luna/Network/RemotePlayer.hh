// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Client.hh"

namespace Luna::Network {
    class CRemotePlayerComponent : private IPacketEventHandler {
    public:
        void Install(CClient& client);

    private:
        bool OnReceivePacket(CClient& client, PacketID id, uint8_t const* data, size_t bitSize);

        void ProcessServerJoin(CClient& client, uint8_t const* rawData, size_t bitSize);
        void ProcessOnFootSync(CClient& client, uint8_t const* rawData, size_t bitSize);
    };
}
