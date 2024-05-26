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
        PADDING(16); // CSimpleTransform placement
        CMatrix* m_Matrix; // CMatrixLink
        PADDING(1064);
        uint8_t* m_Intelligence;
        PADDING(344);

    public:
        CPed() = delete;
        ~CPed() = delete;

        ePedType PedType;

        inline CTaskManager* TaskManager() {
            return reinterpret_cast<CTaskManager*>(m_Intelligence + 4);
        }

        inline CMatrix& Matrix() {
            return **reinterpret_cast<CMatrix**>(
                reinterpret_cast<uint8_t*>(this) + 0x14);
        }

    private:
        PADDING(516);

        static void _Assertions() {
            VALIDATE_OFFSET(CPed, PedType, 0x59C);
        }
    };

    VALIDATE_SIZE(CPed, 1956);
}
