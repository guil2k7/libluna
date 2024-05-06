// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Core/Hook.hh>
#include <Luna/Utils/Memory.hh>
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Utils;

static inline void MakeAbsJump(void* address, void const* destination, bool thumbMode) {
    // ldr.w pc, [pc, #0]
    reinterpret_cast<uint32_t*>(address)[0] = 0xF000F8DF;
    reinterpret_cast<uint32_t*>(address)[1] =
        reinterpret_cast<uint32_t>(destination) | static_cast<uint32_t>(thumbMode);
}

CRawHook::CRawHook() :
    original(nullptr),
    interceptor(nullptr),
    trampoline(nullptr)
{
}

CRawHook::~CRawHook() {
    Deactivate();
    ReleaseTrampoline();
}

void CRawHook::Hook(void* newOriginalPtr, void* newInterceptorPtr) {
    auto newOriginal = reinterpret_cast<uint32_t>(newOriginalPtr);
    auto newInterceptor = reinterpret_cast<uint32_t>(newInterceptorPtr);

    // Check if the original function is in Thumb mode.
    assert((newOriginal & 1) == 1);

    if (original != nullptr) {
        Deactivate();
        ReleaseTrampoline();
    }

    // Clear the least significant bit.
    original = reinterpret_cast<uint8_t*>(newOriginal & 0xFFFFFFFE);
    interceptor = reinterpret_cast<uint8_t*>(newInterceptor & 0xFFFFFFFE);

    // Is the interceptor function in Thumb mode?
    interceptorInThumbMode = static_cast<bool>(newInterceptor & 1);

    trampoline = nullptr;
    activated = false;
}

void CRawHook::Activate() {
    if (activated)
        return;

    activated = true;

    if (trampoline == nullptr) {
        // First call to activate.

        ModifyMemoryProtection(original, 8, PROT_READ | PROT_WRITE | PROT_EXEC);
        CreateTrampoline();
    }

    CreateHook();
}

void CRawHook::Deactivate() {
    if (!activated)
        return;

    activated = false;

    ReleaseHook();
}

void CRawHook::CreateHook() {
    MakeAbsJump(original, interceptor, interceptorInThumbMode);
}

void CRawHook::ReleaseHook() {
    memcpy(original, trampoline, 8);
}

void CRawHook::CreateTrampoline() {
    trampoline = reinterpret_cast<uint8_t*>(mmap(
        nullptr, 16,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_SHARED | MAP_ANONYMOUS,
        0, 0
    ));

    memcpy(trampoline, original, 8);

    MakeAbsJump(
        reinterpret_cast<uint8_t*>(trampoline) + 8,
        reinterpret_cast<uint8_t*>(original) + 8,
        true
    );
}

void CRawHook::ReleaseTrampoline() {
    if (trampoline == nullptr)
        return;

    munmap(trampoline, 16);
    trampoline = nullptr;
}
