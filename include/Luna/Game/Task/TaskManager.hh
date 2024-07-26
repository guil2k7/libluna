// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Task.hh"
#include "../Common.hh"

namespace Luna::Game {

class CTaskManager {
public:
    CTaskManager() = delete;
    ~CTaskManager() = delete;

    inline void SetTask(CTask* task, int index, bool unk) {
        CallMethod<void, CTask*, int, bool>(GameAddress + 0x54397B, this, task, index, unk);
    }
};

} // namespace Luna::Game
