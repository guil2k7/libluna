// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Task.hh"
#include "../Common.hh"

namespace Luna::Game {
    class CTaskManager {
    public:
        CTaskManager() = delete;
        ~CTaskManager() = delete;

        inline void SetTask(CTask *task, int index) {
            CallMethod<void, CTask *, int, bool>(
                GameAddress + 0x54390B, this, task, index, false);
        }
    };
}
