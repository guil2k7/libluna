// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../Common.hh"
#include <cstddef>

namespace Luna::Game {
    class CTask {
    public:
        CTask() = delete;
        ~CTask() = delete;

        inline static void* operator new(size_t size) {
            return CallFunction<void*, size_t>(GameAddress + 0x4E6A71, size);
        }
    };
}
