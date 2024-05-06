// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Task.hh"
#include "../Common.hh"

namespace Luna::Game {
    class CTaskSimplePlayerOnFoot : public CTask {
    public:
        static inline CTaskSimplePlayerOnFoot* Create() {
            auto task = CallFunction<CTaskSimplePlayerOnFoot*, unsigned int>(
                GameAddress + 0x4E6A01, 0x34);

            CallMethod<CTaskSimplePlayerOnFoot*>(
                GameAddress + 0x5474E1, task);

            return task;
        }

    private:
        PADDING(0x34);
    };

    VALIDATE_SIZE(CTaskSimplePlayerOnFoot, 0x34);
}
