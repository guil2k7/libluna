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
    };

    class CPed {
    protected:
        void** vtable;

    private:
        PADDING(16); // CSimpleTransform placement
        CMatrix* matrix; // CMatrixLink
        PADDING(1064);
        uint8_t* intelligence;
        PADDING(344);

    public:
        CPed() = delete;
        ~CPed() = delete;

        ePedType PedType;

        inline CTaskManager* GetTaskManager() {
            return reinterpret_cast<CTaskManager*>(intelligence + 4);
        }

        inline CMatrix& GetMatrix() {
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
