// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Gui.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/imgui_impl_rw.hh>

using namespace Luna;
using namespace Luna::Game;

CGui* CGui::instance = nullptr;

CGui& CGui::Create() {
    assert(instance == nullptr);

    instance = new CGui;
    return *instance;
}

void CGui::Initialise() {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;
    io.MouseSource = ImGuiMouseSource_Mouse;

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui::StyleColorsDark(&style);
    style.ScaleAllSizes(4.0F);

    io.FontGlobalScale = 2.0F;

    ImGui_ImplRW_Init();
}

void CGui::Render() {
    ImGui_ImplRW_NewFrame();
    ImGui::NewFrame();

    for (auto subscriber : subscribers)
        subscriber->Render();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplRW_RenderDrawData(ImGui::GetDrawData());
}
