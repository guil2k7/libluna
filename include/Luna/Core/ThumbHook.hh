// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>

namespace Luna::Core {
    class CThumbRawHook {
    public:
        CThumbRawHook();
        ~CThumbRawHook();

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
        inline void* Original() const {
            return reinterpret_cast<void*>(
                reinterpret_cast<uint32_t>(m_Original) | 1
            );
        }

        /// Gets the interceptor function.
        inline void* Interceptor() const {
            return reinterpret_cast<void*>(
                reinterpret_cast<uint32_t>(m_Interceptor) |
                static_cast<uint32_t>(m_IsInterceptorInThumbMode)
            );
        }

        /// Gets the trampoline to the original function.
        inline void* Trampoline() const {
            if (m_Trampoline == nullptr)
                return Original();

            return reinterpret_cast<void*>(
                reinterpret_cast<uint32_t>(m_Trampoline) | 1
            );
        }

        /// Returns true if the hook is activated.
        inline bool IsActivated() const {
            return m_IsActivated;
        }

    private:
        void CreateHook();
        void ReleaseHook();
        void CreateTrampoline();
        void ReleaseTrampoline();

        uint8_t* m_Original;
        uint8_t* m_Interceptor;
        uint8_t* m_Trampoline;

        bool m_IsActivated;
        bool m_IsInterceptorInThumbMode;
    };

    template<typename FnSignature>
    class CThumbHook : public CThumbRawHook {
    public:
        inline void Hook(void* original, FnSignature interceptor) {
            CThumbRawHook::Hook(original, reinterpret_cast<void*>(interceptor));
        }

        inline void Hook(FnSignature original, FnSignature interceptor) {
            CThumbRawHook::Hook(reinterpret_cast<void*>(original), reinterpret_cast<void*>(interceptor));
        }

        /// Gets the original function.
        inline FnSignature Original() const {
            return reinterpret_cast<FnSignature>(CThumbRawHook::Original());
        }

        /// Gets the interceptor function.
        inline FnSignature Interceptor() const {
            return reinterpret_cast<FnSignature>(CThumbRawHook::Interceptor());
        }

        /// Gets the trampoline to the original function.
        inline FnSignature Trampoline() const {
            return reinterpret_cast<FnSignature>(CThumbRawHook::Trampoline());
        }
    };
}