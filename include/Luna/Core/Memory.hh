// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstddef>

namespace Luna::Core {
    inline size_t AlignValue(size_t value, size_t alignment) {
        if (value < alignment)
            return alignment;
        
        return (value + alignment - 1) / alignment * alignment;
    }

    enum eProtection {
        PROTECTION_READ = 1,
        PROTECTION_WRITE = 1 << 1,
        PROTECTION_EXEC = 1 << 2,
    };

    bool ModifyMemoryProtection(void* address, size_t size, int flags);
    void* AllocMemory(size_t size, int flags);
    void ReleaseMemory(void* addr, size_t size);
}
