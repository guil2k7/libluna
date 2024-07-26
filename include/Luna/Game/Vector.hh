// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "RW/rwplcore.h"
#include "../Serde/Serde.hh"

namespace Luna::Game {

class CVector : public RwV3d {
public:
    constexpr CVector() : RwV3d { 0.0f, 0.0f, 0.0f } {}
    constexpr CVector(float x, float y, float z) : RwV3d { x, y, z } {}

    inline void Set(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }

    inline void Reset() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    inline void Serialize(Serde::ISerializer& serializer) const {
        serializer.SerializeF32(x);
        serializer.SerializeF32(y);
        serializer.SerializeF32(z);
    }

    inline void Deserialize(Serde::IDeserializer& deserializer) {
        x = deserializer.DeserializeF32();
        y = deserializer.DeserializeF32();
        z = deserializer.DeserializeF32();
    }
};

} // namespce Luna::Game
