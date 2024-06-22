// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Game.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/ThumbHook.hh>

using namespace Luna;
using namespace Luna::Game;
using namespace Luna::Core;

static CThumbHook<int (LUNA_STDCALL *)(char const*)> hook_Init3;

static int CGame_Init3(char const* param1) {
    return hook_Init3.Trampoline()(param1);
}

void CGame::InitializeLuna() {
    hook_Init3.Hook(GameAddress + 0x4831A9, CGame_Init3);
    hook_Init3.Activate();
}
