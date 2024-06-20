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
