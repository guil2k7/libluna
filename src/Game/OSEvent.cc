// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

// TODO: Add keyboard support.

#include <Luna/Game/OSEvent.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/imgui_impl_rw.hh>
#include <Luna/Core/ThumbHook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static struct {
    CThumbHook<void (LUNA_STDCALL *)(eTouchAction, int, int, int)> TouchEvent;
    CThumbHook<void (LUNA_STDCALL *)(bool, int, int, bool)> KeyboardEvent;
} hook;

static void HookImpl_AND_TouchEvent(eTouchAction action, int unknown, int x, int y) {
    ImGui_ImplRW_ProcessTouchEvent(action, x, y);

    hook.TouchEvent.Trampoline()(action, unknown, x, y);
}

void OSEvents::InitializeLuna() {
    hook.TouchEvent.Hook(GameAddress + 0x279741, HookImpl_AND_TouchEvent);
    hook.TouchEvent.Activate();
}

void OSEvents::ShowKeyboard() {
    // CallFunction<void, int>(GameAddress + 0x278A89, 1);
}

void OSEvents::HideKeyboard() {
    // CallFunction<void, int>(GameAddress + 0x278A89, 0);
}

bool OSEvents::IsKeyboardShown() {
    // return *reinterpret_cast<uint32_t*>(GameAddress + 0x6E702C);
    return false;
}
