// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Hud.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Core/MemoryExec.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static CFunction<void (LUNA_THISCALL *)(CHud*)> trampoline_DrawAfterFade;

static void LUNA_THISCALL hook_DrawAfterFade(CHud* self) {
    self->DrawAfterFade();
}
 
void CHud::InitialiseLuna() {
    MakeHook(&trampoline_DrawAfterFade, GameAddress + 0x44A6A9, hook_DrawAfterFade);
}

void CHud::DrawAfterFade() {
    trampoline_DrawAfterFade(this);

    CGui::Instance().Render();
}
