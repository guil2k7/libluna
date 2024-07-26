// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Core/Hooker.hh>
#include <Luna/Core/Memory.hh>
#include <Luna/Core/MemoryExec.hh>
#include <cstring>
#include <sys/mman.h>

using namespace Luna;
using namespace Luna::Core;

static inline void MakeArmAbsJump(void* code, void const* destination) {
    // ldr pc, [pc, #-4]
    reinterpret_cast<uint32_t*>(code)[0] = 0xE51FF004;
    reinterpret_cast<void const**>(code)[1] = destination;
}

static inline void MakeThumbAbsJump(void* code, void const* destination) {
    // ldr.w pc, [pc, #0]
    reinterpret_cast<uint32_t*>(code)[0] = 0xF000F8DF;
    reinterpret_cast<void const**>(code)[1] = destination;
}

static void* BuildTrampoline(void const* base, bool thumbMode) {
    void* trampoline = reinterpret_cast<uint8_t*>(mmap(
        nullptr, 16,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_SHARED | MAP_ANONYMOUS,
        0, 0
    ));

    memcpy(trampoline, base, 8);

    if (thumbMode) {
        MakeThumbAbsJump(
            reinterpret_cast<uint8_t*>(trampoline) + 8,
            reinterpret_cast<uint8_t const*>(base) + 8 + 1
        );

        return reinterpret_cast<void*>(reinterpret_cast<uint32_t>(trampoline) | 1);
    }

    MakeArmAbsJump(
        reinterpret_cast<uint8_t*>(trampoline) + 8,
        reinterpret_cast<uint8_t const*>(base) + 8
    );
        
    return trampoline;
}

void* CRawHooker::Hook() {
    bool isOriginalInThumbMode = IsFunctionInThumbInstructionSet(OriginalFn);
    bool isInterceptorInThumbMode = IsFunctionInThumbInstructionSet(InterceptorFn);

    void* originalCode = reinterpret_cast<uint8_t*>(
        reinterpret_cast<uint32_t>(OriginalFn) & 0xFFFFFFFE);

    ModifyMemoryProtection(
        originalCode, 8, PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC);

    void* trampoline = nullptr;

    if (BuildTrampoline)
        trampoline = ::BuildTrampoline(originalCode, isOriginalInThumbMode);

    if (isOriginalInThumbMode)
        MakeThumbAbsJump(originalCode, InterceptorFn);
    else
        MakeArmAbsJump(originalCode, InterceptorFn);

    return trampoline;
}
