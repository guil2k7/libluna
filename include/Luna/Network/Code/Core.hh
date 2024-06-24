// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../Packet.hh"
#include "../../BitSerde.hh"
#include "RakNet/NetworkTypes.h"
#include <cstdint>
#include <string_view>

namespace Luna::Network::Code {
    struct CConnectionRequestAccepted final : public BitSerde::IDeserializable {
        LUNA_DEFINE_PACKET(false, 34)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            deserializer.SkipBytes(6);
            PlayerIndex = deserializer.DeserializeU16();
            SampToken = deserializer.DeserializeU32();
        }

        RakNet::PlayerIndex PlayerIndex;
        uint32_t SampToken;
    };

    struct CClientLogin final : public BitSerde::ISerializable {
        LUNA_DEFINE_PACKET(true, 25)

        void Serialize(BitSerde::CSerializer& serializer) const override {
            serializer.SerializeU32(ClientVersion);
            serializer.SerializeU8(Modded);
            serializer.SerializeU8(Nickname.length());
            serializer.SerializeBytes(reinterpret_cast<uint8_t const*>(Nickname.data()), Nickname.length());
            serializer.SerializeU32(ClientChallengeResponse);
            serializer.SerializeU8(Auth.length());
            serializer.SerializeBytes(reinterpret_cast<uint8_t const*>(Auth.data()), Auth.length());
            serializer.SerializeU8(ClientVersionString.length());
            serializer.SerializeBytes(reinterpret_cast<uint8_t const*>(ClientVersionString.data()), ClientVersionString.length());
            
            // Official clients send the challenge again at the end,
            // while other clients do not.
            serializer.SerializeU32(ClientChallengeResponse);
        }

        uint32_t ClientVersion;
        uint8_t Modded;
        std::string_view Nickname;
        uint32_t ClientChallengeResponse;
        std::string_view Auth;
        std::string_view ClientVersionString;
    };
}
