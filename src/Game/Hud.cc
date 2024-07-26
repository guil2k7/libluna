// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Game/Hud.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Core/Hooker.hh>
#include <Luna/Network/Client.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;
using namespace Luna::Network;

static void (LUNA_THISCALL *trampoline_DrawAfterFade)(CHud*);

static void LUNA_THISCALL HookImpl_DrawAfterFade(CHud* self) {
    self->DrawAfterFade();
}
 
void CHud::InitializeLuna() {
    trampoline_DrawAfterFade = CHooker(GameAddress + 0x44A6A9, HookImpl_DrawAfterFade, true).Hook();
}

void CHud::DrawAfterFade() {
    trampoline_DrawAfterFade(this);

    client->Process();

    CGui::Instance().Render();
}
