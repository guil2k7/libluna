// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Pad.hh>
#include <Luna/Core/Hook.hh>
#include <spdlog/spdlog.h>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static CHook<CPad* (LUNA_STDCALL *)(int)> hook_GetPad;

void CPadMod::Install() {
    *reinterpret_cast<CPad**>(GameAddress + 0x687B14) = new CPad[1024];;

    hook_GetPad.Hook(
        GameAddress + 0x408CA5,
        [](int id) {
            if (id == 1)
                id = CPad::MapPad1To;

            return CPad::GetPad(id);
        }
    );

    hook_GetPad.Activate();
}

int CPad::MapPad1To = 1;
