// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Hud.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Core/Hook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static CHook<void (LUNA_THISCALL *)(CHud*)> hook_DrawAfterFade;

void CHud::InitialiseLuna() {
    hook_DrawAfterFade.Hook(
        GameAddress + 0x44A6A9,
        [](CHud* self) { return self->DrawAfterFade(); }
    );
};

void CHud::DrawAfterFade() {
    hook_DrawAfterFade.Trampoline()(this);

    CGui::Instance().Render();
}
