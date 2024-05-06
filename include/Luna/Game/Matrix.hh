// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Common.hh"
#include "Vector.hh"
#include <cstdint>

namespace Luna::Game {
    class CMatrix {
    public:
        void ResetOrientation() {
            Right.Set(1.0F, 0.0F, 0.0F);
            Forward.Set(0.0F, 1.0F, 0.0F);
            Up.Set(0.0F, 0.0F, 1.0F);
        }

        void SetUnity() {
            ResetOrientation();
            Position.Reset();
        }

        CVector Right;
        uint32_t Flags;
        CVector Forward;
        PADDING(4);
        CVector Up;
        PADDING(4);
        CVector Position;
    };

    // VALIDATE_OFFSET(CMatrix, right, 0);
    VALIDATE_OFFSET(CMatrix, Forward, 0x10);
    // VALIDATE_OFFSET(CMatrix, pos, 0x30);

    VALIDATE_SIZE(CMatrix, 60);
}
