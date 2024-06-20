// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Hud.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Core/ThumbHook.hh>
#include <Luna/Network/Client.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;
using namespace Luna::Network;

static CThumbHook<void (LUNA_THISCALL *)(CHud*)> hook_DrawAfterFade;

static void LUNA_THISCALL HookImpl_DrawAfterFade(CHud* self) {
    self->DrawAfterFade();
}
 
void CHud::InitializeLuna() {
    hook_DrawAfterFade.Hook(GameAddress + 0x44A6A9, HookImpl_DrawAfterFade);
    hook_DrawAfterFade.Activate();
}

void CHud::DrawAfterFade() {
    hook_DrawAfterFade.Trampoline()(this);

    client->Process();

    CGui::Instance().Render();
}
