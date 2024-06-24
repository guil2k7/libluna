// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>

namespace Luna::Network {
    typedef uint8_t PacketID;

    #define LUNA_DEFINE_PACKET(isRPC, id) \
    static constexpr bool PACKET_IS_RPC = isRPC; \
    static constexpr PacketID PACKET_ID = id;

    template<typename T>
    inline constexpr bool IsRPC() {
        return T::PACKET_IS_RPC;
    }

    template<typename T>
    inline constexpr PacketID GetPacketID() {
        return T::PACKET_ID;
    }
}
