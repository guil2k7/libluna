// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

// TODO: Add keyboard support.

#include "spdlog/spdlog.h"
#include <Luna/Game/OSEvent.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/imgui_impl_rw.hh>
#include <Luna/Core/Hook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static CHook<void (LUNA_STDCALL *)(eTouchAction, int, int, int)> hook_TouchEvent;
static CHook<void (LUNA_STDCALL *)(bool, int, int, bool)> hook_KeyboardEvent;

static void AND_TouchEvent(eTouchAction action, int unknown, int x, int y) {
    ImGui_ImplRW_ProcessTouchEvent(action, x, y);

    hook_TouchEvent.GetTrampoline()(action, unknown, x, y);
}

static void AND_KeyboardEvent(bool param1, int param2, int param3, bool param4) {
    ImGui_ImplRW_ProcessKeyboardEvent(param2, param3 + 0xFFFFFFFF > 0, param1);

    hook_KeyboardEvent.GetTrampoline()(param1, param2, param3, param4);
}

void OSEventsMod::Install() {
    hook_TouchEvent.Hook(GameAddress + 0x2797C1, AND_TouchEvent);
    // hook_KeyboardEvent.Hook(GameAddress + 0x2789DD, AND_KeyboardEvent);

    hook_TouchEvent.Activate();
    // hook_KeyboardEvent.Activate();
}

void Game::ShowKeyboard() {
    // CallFunction<void, int>(GameAddress + 0x278A89, 1);
}

void Game::HideKeyboard() {
    // CallFunction<void, int>(GameAddress + 0x278A89, 0);
}

bool Game::IsKeyboardShown() {
    // return *reinterpret_cast<uint32_t*>(GameAddress + 0x6E702C);
    return false;
}
