// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Game/Game.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/Hooker.hh>

using namespace Luna;
using namespace Luna::Game;
using namespace Luna::Core;

static int (LUNA_STDCALL *trampoline_Init3)(char const*);

static int CGame_Init3(char const* param1) {
    return trampoline_Init3(param1);
}

void CGame::InitializeLuna() {
    trampoline_Init3 = CHooker(GameAddress + 0x4831A9, CGame_Init3, true).Hook();
}
