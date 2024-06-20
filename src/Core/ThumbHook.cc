// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Core/ThumbHook.hh>
#include <Luna/Core/Memory.hh>
#include <Luna/Core/MemoryExec.hh>
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

using namespace Luna;
using namespace Luna::Core;

constexpr size_t ABS_JUMP_SIZE = 8;

static inline void MakeAbsJump(void* address, void const* destination, bool thumbMode) {
    // ldr.w pc, [pc, #0]
    reinterpret_cast<uint32_t*>(address)[0] = 0xF000F8DF;
    reinterpret_cast<uint32_t*>(address)[1]
        = reinterpret_cast<uint32_t>(destination) | (thumbMode ? 1 : 0);
}

CThumbRawHook::CThumbRawHook() :
    m_Original(nullptr), m_Interceptor(nullptr), m_Trampoline(nullptr) {}

CThumbRawHook::~CThumbRawHook() {
    Deactivate();
    ReleaseTrampoline();
}

void CThumbRawHook::Hook(void* original, void* interceptor) {
    // Check if the original function is in Thumb mode.
    assert(IsFunctionInThumbInstructionSet(original));

    if (m_Original != nullptr) {
        Deactivate();
        ReleaseTrampoline();
    }

    m_Original = reinterpret_cast<uint8_t*>(
        reinterpret_cast<uint32_t>(original) & 0xFFFFFFFE);

    m_Interceptor = reinterpret_cast<uint8_t*>(
        reinterpret_cast<uint32_t>(interceptor) & 0xFFFFFFFE);

    m_IsInterceptorInThumbMode = IsFunctionInThumbInstructionSet(interceptor);
    m_Trampoline = nullptr;
    m_IsActivated = false;
}

void CThumbRawHook::Activate() {
    if (m_IsActivated)
        return;

    m_IsActivated = true;

    if (m_Trampoline == nullptr) {
        // First call to activate.

        ModifyMemoryProtection(m_Original, 8, PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC);
        CreateTrampoline();
    }

    CreateHook();
}

void CThumbRawHook::Deactivate() {
    if (!m_IsActivated)
        return;

    m_IsActivated = false;

    ReleaseHook();
}

void CThumbRawHook::CreateHook() {
    MakeAbsJump(m_Original, m_Interceptor, m_IsInterceptorInThumbMode);
}

void CThumbRawHook::ReleaseHook() {
    memcpy(m_Original, m_Trampoline, 8);
}

void CThumbRawHook::CreateTrampoline() {
    m_Trampoline = reinterpret_cast<uint8_t*>(mmap(
        nullptr, 16,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_SHARED | MAP_ANONYMOUS,
        0, 0
    ));

    memcpy(m_Trampoline, m_Original, 8);

    MakeAbsJump(
        reinterpret_cast<uint8_t*>(m_Trampoline) + 8,
        reinterpret_cast<uint8_t*>(m_Original) + 8,
        true
    );
}

void CThumbRawHook::ReleaseTrampoline() {
    if (m_Trampoline == nullptr)
        return;

    munmap(m_Trampoline, 16);
    m_Trampoline = nullptr;
}