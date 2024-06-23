// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../Packet.hh"
#include "RakNet/NetworkTypes.h"
#include <cstdint>
#include <string_view>

namespace Luna::Network::Code {
    struct CConnectionRequestAccepted final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(34, false)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            deserializer.SkipBytes(7);
            PlayerIndex = deserializer.DeserializeU16();
            SampToken = deserializer.DeserializeU32();
        }

        RakNet::PlayerIndex PlayerIndex;
        uint32_t SampToken;
    };

    struct CClientJoin final : public IPacketSerializable {
        LUNA_DEFINE_PACKET(25, true)

        void Serialize(BitSerde::CSerializer& serializer) const override {
            serializer.SerializeU8(Version);
            serializer.SerializeU8(Mod);
            serializer.SerializeU8(Nickname.length());
            serializer.SerializeU32(ClientChallengeResponse);
            serializer.SerializeU8(Auth.length());
            serializer.SerializeBytes(reinterpret_cast<uint8_t const*>(Auth.data()), Auth.length());
            serializer.SerializeU8(ClientVersion.length());
            serializer.SerializeBytes(reinterpret_cast<uint8_t const*>(ClientVersion.data()), ClientVersion.length());
            serializer.SerializeU32(ClientChallengeResponse);
        }

        uint32_t Version;
        uint8_t Mod;
        std::string_view Nickname;
        uint32_t ClientChallengeResponse;
        std::string_view Auth;
        std::string_view ClientVersion;
    };
}
