// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "RW/rwplcore.h"
#include "../Serde/Serde.hh"

namespace Luna::Game {
    class CVector : public RwV3d {
    public:
        constexpr CVector() : RwV3d { 0.0F, 0.0F, 0.0F } {}
        constexpr CVector(float x, float y, float z) : RwV3d { x, y, z } {}

        inline void Set(float x_, float y_, float z_) {
            x = x_;
            y = y_;
            z = z_;
        }

        inline void Reset() {
            x = 0.0F;
            y = 0.0F;
            z = 0.0F;
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

    class CVector4D : public RwV4d {
    public:
        constexpr CVector4D() : RwV4d { 0.0F, 0.0F, 0.0F, 0.0F } {}
        constexpr CVector4D(float w, float x, float y, float z) : RwV4d { x, y, z, w } {}

        inline void Serialize(Serde::ISerializer& serializer) const {
            serializer.SerializeF32(w);
            serializer.SerializeF32(x);
            serializer.SerializeF32(y);
            serializer.SerializeF32(z);
        }

        inline void Deserialize(Serde::IDeserializer& deserializer) {
            w = deserializer.DeserializeF32();
            x = deserializer.DeserializeF32();
            y = deserializer.DeserializeF32();
            z = deserializer.DeserializeF32();
        }
    };
}
