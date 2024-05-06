#pragma once

#include <imgui.h>
#include "OSEvent.hh"

bool ImGui_ImplRW_Init();
void ImGui_ImplRW_Shutdown();
void ImGui_ImplRW_NewFrame();
void ImGui_ImplRW_RenderDrawData(ImDrawData* drawData);
void ImGui_ImplRW_ProcessTouchEvent(Luna::Game::eTouchAction action, int x, int y);
void ImGui_ImplRW_ProcessKeyboardEvent(int key, bool shift, bool down);
