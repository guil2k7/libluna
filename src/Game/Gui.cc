// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Game/Gui.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/imgui_impl_rw.hh>

using namespace Luna;
using namespace Luna::Game;

CGui* CGui::m_Instance = nullptr;

void CGui::Initialize() {
    assert(m_Instance == nullptr);

    m_Instance = new CGui;

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;
    io.MouseSource = ImGuiMouseSource_Mouse;

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui::StyleColorsDark(&style);
    style.ScaleAllSizes(4.0f);

    io.FontGlobalScale = 2.0f;

    ImGui_ImplRW_Init();
}

void CGui::Render() {
    ImGui_ImplRW_NewFrame();
    ImGui::NewFrame();

    for (auto subscriber : m_Subscribers)
        subscriber->Render();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplRW_RenderDrawData(ImGui::GetDrawData());
}
