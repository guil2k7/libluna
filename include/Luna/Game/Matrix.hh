// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Common.hh"
#include "Vector.hh"
#include <cstdint>

namespace Luna::Game {

class CMatrix {
public:
    inline void ResetOrientation() {
        Right.Set(1.0f, 0.0f, 0.0f);
        Forward.Set(0.0f, 1.0f, 0.0f);
        Up.Set(0.0f, 0.0f, 1.0f);
    }

    inline void SetUnity() {
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

VALIDATE_SIZE(CMatrix, 60);

// VALIDATE_OFFSET(CMatrix, right, 0);
VALIDATE_OFFSET(CMatrix, Forward, 0x10);
// VALIDATE_OFFSET(CMatrix, pos, 0x30);

} // namespce Luna::Game
