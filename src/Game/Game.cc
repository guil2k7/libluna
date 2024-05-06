// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Game.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Core/Hook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static CHook<int (LUNA_STDCALL *)(char const*)> hook_Init3;

void CGameMod::Install() {
    hook_Init3.Hook(GameAddress + 0x483139, CGame::Init3);
    hook_Init3.Activate();
}

int CGame::Init3(char const* unknown) {
    return hook_Init3.GetTrampoline()(unknown);
}
