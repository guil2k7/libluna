// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../Packet.hh"
#include "../../Serde/Serde.hh"
#include "RakNet/NetworkTypes.h"
#include <cstdint>
#include <string_view>

namespace Luna::Network::Code {

struct CConnectionRequestAccepted final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(false, 34)

    void Deserialize(Serde::IDeserializer& deserializer) override;

    RakNet::PlayerIndex PlayerIndex;
    uint32_t SampToken;
};

struct CClientLogin final : public Serde::ISerializable {
    LUNA_DEFINE_PACKET(true, 25)

    void Serialize(Serde::ISerializer& serializer) const override;

    uint32_t ClientVersion;
    uint8_t Modded;
    std::string_view Nickname;
    uint32_t ClientChallengeResponse;
    std::string_view Auth;
    std::string_view ClientVersionString;
};

} // namespace Luna::Network::Code

#include "Core.inl"
