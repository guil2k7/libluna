// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>

namespace Luna::Core {
    class CRawThumbHook {
    public:
        CRawThumbHook();
        ~CRawThumbHook();

        /// TODO: Documentate this function.
        void Hook(void* original, void const* interceptor);

        /// Gets the trampoline to the original function.
        inline void* Trampoline() const {
            return reinterpret_cast<void*>(
                reinterpret_cast<uint32_t>(m_Trampoline) | 1
            );
        }

    protected:
        void CreateHook(uint8_t* original, uint8_t const* interceptor);
        void CreateTrampoline(uint8_t const* original);

        uint8_t* m_Trampoline;
    };

    template<typename FnSignature>
    class CThumbHook : public CRawThumbHook {
    public:
        inline void Hook(void* original, FnSignature interceptor) {
            CRawThumbHook::Hook(original, reinterpret_cast<void*>(interceptor));
        }

        inline void Hook(FnSignature original, FnSignature interceptor) {
            CRawThumbHook::Hook(reinterpret_cast<void*>(original), reinterpret_cast<void*>(interceptor));
        }

        /// Gets the trampoline to the original function.
        inline FnSignature Trampoline() const {
            return reinterpret_cast<FnSignature>(CRawThumbHook::Trampoline());
        }
    };
}
