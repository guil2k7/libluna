// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

namespace Luna::Core {
    class CRawHooker {
    public:
        CRawHooker() :
            OriginalFn(nullptr), InterceptorFn(nullptr), BuildTrampoline(false) {} 

        CRawHooker(void* originalFn, void const* interceptorFn, bool buildTrampoline) :
            OriginalFn(originalFn), InterceptorFn(interceptorFn), BuildTrampoline(buildTrampoline) {} 

        void* OriginalFn;
        void const* InterceptorFn;
        bool BuildTrampoline;

        /// Returns the trampoline if `BuildTrampoline` is true; otherwise
        /// false.
        void* Hook();
    };

    template<typename FnSignature>
    class CHooker : public CRawHooker {
    public:
        CHooker() : CRawHooker() {}

        CHooker(void* originalFn, FnSignature interceptorFn, bool buildTrampoline) :
            CRawHooker(originalFn, reinterpret_cast<void const*>(interceptorFn), buildTrampoline) {}

        CHooker(FnSignature originalFn, FnSignature interceptorFn, bool buildTrampoline) :
            CRawHooker(reinterpret_cast<void*>(originalFn), reinterpret_cast<void const*>(interceptorFn), buildTrampoline) {}

        inline CHooker& SetOriginalFn(void* originalFn) {
            OriginalFn = originalFn;
            return *this;
        }

        inline CHooker& SetOriginalFn(FnSignature originalFn) {
            OriginalFn = reinterpret_cast<void*>(originalFn);
            return *this;
        }

        inline CHooker& SetInterceptorFn(FnSignature interceptorFn) {
            InterceptorFn = reinterpret_cast<void*>(interceptorFn);
            return *this;
        }

        inline CHooker& SetBuildTrampoline(bool value) {
            BuildTrampoline = value;
            return *this;
        }

        /// Returns the trampoline if `BuildTrampoline` is true; otherwise
        /// false.
        inline FnSignature Hook() {
            return reinterpret_cast<FnSignature>(CRawHooker::Hook());
        }
    };
}
