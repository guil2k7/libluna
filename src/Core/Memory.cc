// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Core/Memory.hh>
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

void* Core::AllocMemory(size_t size, int flags) {
    return mmap(
        nullptr, size, ConvertProtectionFlagsToOS(flags),
        MAP_PRIVATE | MAP_ANONYMOUS,
        0, 0
    );
}

void Core::ReleaseMemory(void* addr, size_t size) {
    munmap(addr, size);
}
