// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Common.hh"
#include "Matrix.hh"
#include "Task/TaskManager.hh"
#include <cstdint>

namespace Luna::Game {
    
enum ePedType {
    PED_TYPE_PLAYER1,
    PED_TYPE_PLAYER2,
    PED_TYPE_PLAYER_NETWORK,
};

class CPed {
protected:
    void** vtable;

private:
    // Offset: 4.
    PADDING(16); // CSimpleTransform placement.

    // Offset: 20. CMatrixLink
    CMatrix* m_Matrix;
    PADDING(1064);

    // Offset: 1088.
    uint8_t* m_Intelligence;
    PADDING(256);

    // Offset: 1348.
    float m_Health;
    float m_MaxHealth;
    PADDING(80);

public:
    CPed() = delete;
    ~CPed() = delete;

    // Offset: 1436.
    ePedType PedType;

    inline bool IsPlayer() const {
        return PedType <= PED_TYPE_PLAYER_NETWORK;
    }

    inline CTaskManager* TaskManager() {
        return reinterpret_cast<CTaskManager*>(m_Intelligence + 4);
    }

    inline CMatrix& Matrix() {
        return **reinterpret_cast<CMatrix**>(
            reinterpret_cast<uint8_t*>(this) + 0x14);
    }

    void SetHealth(float value);

    inline float Health() const {
        return m_Health;
    }

private:
    PADDING(516);

    static void _Assertions() {
        VALIDATE_OFFSET(CPed, PedType, 1436);
        VALIDATE_OFFSET(CPed, m_MaxHealth, 1352);
    }
};

VALIDATE_SIZE(CPed, 1956);

} // namespce Luna::Game
