// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Utils/Memory.hh>
#include <unistd.h>
#include <sys/mman.h>

using namespace Luna;
using namespace Luna::Utils;

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

bool Utils::ModifyMemoryProtection(void* address, size_t size, int flags) {
    int pageSize = getpagesize();

    void* pageStart = reinterpret_cast<void*>(
        reinterpret_cast<uintptr_t>(address) & ~(pageSize - 1));

    int osFlags = ConvertProtectionFlagsToOS(flags);

    return mprotect(pageStart, AlignValue(size, pageSize), osFlags) == 0;
}
