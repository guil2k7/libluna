// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../BitSerde.hh"
#include <RakNet/PacketPriority.h>
#include <cstdint>

namespace Luna::Network {
    struct IPacketHeader {
        virtual uint8_t ID() const = 0;
        virtual bool IsRPC() const = 0;
    };

    struct IPacketSerializable : public IPacketHeader, public BitSerde::ISerializable {};
    struct IPacketDeserializable : public IPacketHeader, public BitSerde::IDeserializable {};

    #define LUNA_DEFINE_PACKET(id, isRPC) \
    inline uint8_t ID() const override { return id; } \
    inline bool IsRPC() const override { return isRPC; }
}
