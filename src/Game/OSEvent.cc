// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

// TODO: Add keyboard support.

#include <Luna/Game/OSEvent.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/imgui_impl_rw.hh>
#include <Luna/Core/Hooker.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static struct {
    void (LUNA_STDCALL *TouchEvent)(eTouchAction, int, int, int);
    void (LUNA_STDCALL *KeyboardEvent)(bool, int, int, bool);
} trampoline;

static void HookImpl_AND_TouchEvent(eTouchAction action, int unknown, int x, int y) {
    ImGui_ImplRW_ProcessTouchEvent(action, x, y);

    trampoline.TouchEvent(action, unknown, x, y);
}

void OSEvents::InitializeLuna() {
    trampoline.TouchEvent = CHooker(GameAddress + 0x279741, HookImpl_AND_TouchEvent, true).Hook();
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
