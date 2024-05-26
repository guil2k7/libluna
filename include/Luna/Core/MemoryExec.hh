// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Memory.hh"
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
    
    constexpr size_t ABS_JUMP_SIZE = 8;

    static inline void MakeAbsJump(void* address, void const* destination, bool thumbMode) {
        // ldr.w pc, [pc, #0]
        reinterpret_cast<uint32_t*>(address)[0] = 0xF000F8DF;
        reinterpret_cast<uint32_t*>(address)[1]
            = reinterpret_cast<uint32_t>(destination) | (thumbMode ? 1 : 0);
    }

    class CExecutable {
    public:
        CExecutable() : m_Code(nullptr), m_CodeSize(0) {}
        ~CExecutable();

        inline bool Allocate(size_t size) {
            if (m_Code != nullptr)
                return false;

            m_Code = reinterpret_cast<uint8_t*>(AllocMemory(
                size, PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC));

            m_CodeSize = size;

            return true;
        }

        inline uint8_t* Code() {
            return m_Code;
        }

        inline uint8_t const* CodeConst() const {
            return m_Code;
        }

        inline size_t CodeSize() const {
            return m_CodeSize;
        }

    private:
        uint8_t* m_Code;
        size_t m_CodeSize;
    };

    template<typename FnSign, bool ThumbInstructionSet = true>
    class CFunction : public CExecutable {
    public:
        template<typename... Args>
        inline auto operator ()(Args... args) const {
            return reinterpret_cast<FnSign>(
                reinterpret_cast<uintptr_t>(CExecutable::CodeConst()) | ThumbInstructionSet
            )(args...);
        }
    };

    void MakeHook(CExecutable* hook, void* function, void const* newFunction);

    template<typename FnSign>
    void MakeHook(CExecutable* hook, void* function, FnSign newFunction) {
        return MakeHook(hook, function, reinterpret_cast<void const*>(newFunction));
    }
}
