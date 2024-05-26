// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Core/MemoryExec.hh>
#include <Luna/Core/Memory.hh>
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

using namespace Luna;
using namespace Luna::Core;

void Core::MakeNop(void* address, size_t size) {
    assert((size % 2) == 0);

    size /= 2;

    for (size_t i = 0; i < size; ++i)
        reinterpret_cast<uint16_t*>(address)[i] = 0x46C0; // mov r8, r8
}

void Core::MakeHook(CExecutable* hook, void* _function, void const* _newFunction) {
    auto uFunction = reinterpret_cast<uintptr_t>(_function);
    auto uNewFunction = reinterpret_cast<uintptr_t>(_newFunction);

    assert(IsFunctionInThumbInstructionSet(uFunction));
    assert(IsFunctionInThumbInstructionSet(uNewFunction));

    // Clear the least significant bit.
    uFunction &= 0xFFFFFFFE;
    uNewFunction &= 0xFFFFFFFE;

    auto function = reinterpret_cast<uint8_t*>(uFunction);
    auto newFunction = reinterpret_cast<uint8_t const*>(uNewFunction);

    ModifyMemoryProtection(
        function, ABS_JUMP_SIZE,
        PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC
    );

    if (hook != nullptr) {
        hook->Allocate(ABS_JUMP_SIZE * 2);

        memcpy(hook->Code(), function, ABS_JUMP_SIZE);

        MakeAbsJump(
            hook->Code() + ABS_JUMP_SIZE,
            function + ABS_JUMP_SIZE,
            true
        );
    }
    
    MakeAbsJump(function, newFunction, true);
    FlushCache(function, ABS_JUMP_SIZE);

    // ModifyMemoryProtection(
    //     function, ABS_JUMP_SIZE,
    //     PROTECTION_READ | PROTECTION_EXEC
    // );
}

CExecutable::~CExecutable() {
    if (m_Code != nullptr)
        munmap(m_Code, m_CodeSize);
}
