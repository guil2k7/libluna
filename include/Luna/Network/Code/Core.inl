// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

namespace Luna::Network::Code {

inline void CConnectionRequestAccepted::Deserialize(Serde::IDeserializer& deserializer) {
    deserializer.SkipBytes(6);
    PlayerIndex = deserializer.DeserializeU16();
    SampToken = deserializer.DeserializeU32();
}

inline void CClientLogin::Serialize(Serde::ISerializer& serializer) const {
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

} // namespace Luna::Network::Code
