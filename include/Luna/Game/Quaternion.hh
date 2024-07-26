// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Matrix.hh"
#include "../Serde/Serde.hh"
#include <cmath>

namespace Luna::Game {

class CQuaternion {
public:
    constexpr CQuaternion() : W{}, X{}, Y{}, Z{} {}
    constexpr CQuaternion(float w, float x, float y, float z) : W(w), X(x), Y(y), Z(z) {}

    void SetFromMatrix(CMatrix const& matrix);

    float Length() const;
    void Normalize();

    inline void Serialize(Serde::ISerializer& serializer) const {
        serializer.SerializeBytes(reinterpret_cast<uint8_t const*>(this), sizeof (*this));
    }

    inline void Deserialize(Serde::IDeserializer& deserializer) {
        deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(this), sizeof (*this));
    }

    float W;
    float X;
    float Y;
    float Z;
};

inline float CQuaternion::Length() const {
    return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

inline void CQuaternion::Normalize() {
    float f = 1.0f / Length();
    
    W *= f;
    X *= f;
    Y *= f;
    Z *= f;
}

} // namespace Luna::Game 
