// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>

namespace Luna::Core {
    class CRawHook {
    public:
        CRawHook();
        ~CRawHook();

        /// TODO: Documentate this function.
        void Hook(void* original, void* interceptor);

        /// Activates the hook.
        ///
        /// All calls directed to the original function will be
        /// redirected to the interceptor function.
        void Activate();

        /// Deactivates the hook.
        ///
        /// All calls directed to the original function will NOT be
        /// redirected to the interceptor function.
        void Deactivate();

        /// Gets the original function.
        inline void* GetOriginal() const {
            return reinterpret_cast<void* >(
                reinterpret_cast<uint32_t>(original) | 1
            );
        }

        /// Gets the interceptor function.
        inline void* GetInterceptor() const {
            return reinterpret_cast<void* >(
                reinterpret_cast<uint32_t>(interceptor) |
                static_cast<uint32_t>(interceptorInThumbMode)
            );
        }

        /// Gets the trampoline to the original function.
        inline void* GetTrampoline() const {
            if (trampoline == nullptr)
                return GetOriginal();

            return reinterpret_cast<void* >(
                reinterpret_cast<uint32_t>(trampoline) | 1
            );
        }

        /// Returns true if the hook is activated.
        inline bool IsActivated() const {
            return activated;
        }

    private:
        void CreateHook();
        void ReleaseHook();
        void CreateTrampoline();
        void ReleaseTrampoline();

        uint8_t* original;
        uint8_t* interceptor;
        uint8_t* trampoline;

        bool activated;
        bool interceptorInThumbMode;
    };

    template<typename FnSignature>
    class CHook : public CRawHook {
    public:
        inline void Hook(void* original, FnSignature interceptor) {
            CRawHook::Hook(original, reinterpret_cast<void* >(interceptor));
        }

        inline void Hook(FnSignature original, FnSignature interceptor) {
            CRawHook::Hook(reinterpret_cast<void* >(original), reinterpret_cast<void* >(interceptor));
        }

        /// Gets the original function.
        inline FnSignature GetOriginal() const {
            return reinterpret_cast<FnSignature>(CRawHook::GetOriginal());
        }

        /// Gets the interceptor function.
        inline FnSignature GetInterceptor() const {
            return reinterpret_cast<FnSignature>(CRawHook::GetInterceptor());
        }

        /// Gets the trampoline to the original function.
        inline FnSignature GetTrampoline() const {
            return reinterpret_cast<FnSignature>(CRawHook::GetTrampoline());
        }
    };
}
