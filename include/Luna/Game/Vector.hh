// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "RW/rwplcore.h"

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
    };

    class CVector4D : public RwV4d {
    public:
        constexpr CVector4D() : RwV4d { 0.0F, 0.0F, 0.0F, 0.0F } {}
        constexpr CVector4D(float x, float y, float z, float w) : RwV4d { x, y, z, w } {}
    };
}
