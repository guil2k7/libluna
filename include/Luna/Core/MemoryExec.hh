// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>

namespace Luna::Core {
    /// Flushes the contents of the instruction cache.
    inline void FlushCache(void* address, size_t size) {
        __builtin___clear_cache(
            reinterpret_cast<char*>(address),
            &reinterpret_cast<char*>(address)[size]
        );
    }

    template<typename T>
    inline bool IsFunctionInThumbInstructionSet(T val) {
        return reinterpret_cast<uintptr_t>(val) & 1;
    }

    void MakeNop(void* address, size_t size);
}
