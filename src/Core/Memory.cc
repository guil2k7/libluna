// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Core/Memory.hh>
#include <cassert>
#include <unistd.h>
#include <sys/mman.h>

using namespace Luna;
using namespace Luna::Core;

static int ConvertProtectionFlagsToOS(int flags) {
    int osFlags = 0;

    if (flags & PROTECTION_READ)
        osFlags |= PROT_READ;

    if (flags & PROTECTION_WRITE)
        osFlags |= PROT_WRITE;

    if (flags & PROTECTION_EXEC)
        osFlags |= PROT_EXEC;

    return osFlags;
}

bool Core::ModifyMemoryProtection(void* address, size_t size, int flags) {
    int pageSize = getpagesize();

    void* pageStart = reinterpret_cast<void*>(
        reinterpret_cast<uintptr_t>(address) & ~(pageSize - 1));

    int osFlags = ConvertProtectionFlagsToOS(flags);

    return mprotect(pageStart, AlignValue(size, pageSize), osFlags) == 0;
}

void Core::MakeNop(void* address, size_t size) {
    assert((size % 2) == 0);

    size /= 2;

    for (size_t i = 0; i < size; ++i)
        reinterpret_cast<uint16_t*>(address)[i] = 0x46C0; // mov r8, r8
}
