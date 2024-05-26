// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>
#include <cstddef>

namespace Luna::Core {
    inline size_t AlignValue(size_t value, size_t alignment) {
        if (value < alignment)
            return alignment;
        
        return (value + alignment - 1) / alignment * alignment;
    }

    /// Flushes the contents of the instruction cache.
    inline void FlushCache(void* address, size_t size) {
        __builtin___clear_cache(
            reinterpret_cast<char*>(address),
            &reinterpret_cast<char*>(address)[size]
        );
    }

    void MakeNop(void* address, size_t size);
    
    static inline void MakeAbsJump(void* address, void const* destination, bool thumbMode) {
        // ldr.w pc, [pc, #0]
        reinterpret_cast<uint32_t*>(address)[0] = 0xF000F8DF;
        reinterpret_cast<uint32_t*>(address)[1]
            = reinterpret_cast<uint32_t>(destination) | (thumbMode ? 1 : 0);
    }

    enum eProtection {
        PROTECTION_READ = 1,
        PROTECTION_WRITE = 1 << 1,
        PROTECTION_EXEC = 1 << 2,
    };

    bool ModifyMemoryProtection(void* address, size_t size, int flags);
}
