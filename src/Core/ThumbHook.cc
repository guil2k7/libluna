// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Core/ThumbHook.hh>
#include <Luna/Core/Memory.hh>
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

using namespace Luna;
using namespace Luna::Core;

#define ABS_JUMP_SIZE    8
#define HOOK_SIZE        8
#define TRAMPOLINE_SIZE (HOOK_SIZE + ABS_JUMP_SIZE)

CRawThumbHook::CRawThumbHook() {
    m_Trampoline = nullptr;
}

CRawThumbHook::~CRawThumbHook() {
    if (m_Trampoline != nullptr)
        munmap(m_Trampoline, TRAMPOLINE_SIZE);
}

void CRawThumbHook::Hook(void* originalFunc, void const* interceptorFunc) {
    assert(m_Trampoline == nullptr);
    
    auto original = reinterpret_cast<uint32_t>(originalFunc);
    auto interceptor = reinterpret_cast<uint32_t>(interceptorFunc);

    // Check if the functions is in Thumb mode.
    assert((original & 1) == 1);
    assert((interceptor & 1) == 1);

    // Clear the least significant bit.
    original &= 0xFFFFFFFE;
    interceptor &= 0xFFFFFFFE;

    ModifyMemoryProtection(
        reinterpret_cast<void*>(original), HOOK_SIZE,
        PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC
    );

    CreateTrampoline(reinterpret_cast<uint8_t const*>(original));
}

void CRawThumbHook::CreateHook(uint8_t* original, uint8_t const* interceptor) {
    MakeAbsJump(original, interceptor, true);
    FlushCache(original, HOOK_SIZE);
}

void CRawThumbHook::CreateTrampoline(uint8_t const* original) {
    m_Trampoline = reinterpret_cast<uint8_t*>(mmap(
        nullptr, TRAMPOLINE_SIZE,
        PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC,
        MAP_PRIVATE | MAP_ANONYMOUS,
        0, 0
    ));

    memcpy(m_Trampoline, original, HOOK_SIZE);

    MakeAbsJump(
        reinterpret_cast<uint8_t*>(m_Trampoline) + HOOK_SIZE,
        reinterpret_cast<uint8_t const*>(original) + HOOK_SIZE,
        true
    );
}
