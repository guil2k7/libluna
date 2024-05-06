// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <jni.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/android_sink.h>

#include <Luna/Game/Gui.hh>
#include <Luna/Game/imgui_impl_rw.hh>
#include <Luna/Game/Mod.hh>
#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/World.hh>
#include <Luna/Game/Task/TaskSimplePlayerOnFoot.hh>

using namespace Luna;
using namespace Luna::Game;

class DebugMenu final : public IGuiWidget {
public:
    void Render() {
        ImGui::Begin("Debug Menu");

        ImGui::SliderInt("ID", &id, 0, 1000);

        if (ImGui::Button("<<"))
            id -= 1;

        ImGui::SameLine();

        if (ImGui::Button(">>"))
            id += 1;

        if (ImGui::Button("Create player")) {
            CPlayerPed::SetupPlayerPed(id);

            CPlayerPed* player = CWorld::Players()[id].PlayerPed;

            player->GetTaskManager()->SetTask(
                CTaskSimplePlayerOnFoot::Create(), 4);
        }

        ImGui::Text("Position:");
        ImGui::InputFloat("X", &pos.x);
        ImGui::InputFloat("Y", &pos.y);
        ImGui::InputFloat("Z", &pos.z);

        if (ImGui::Button("Set Position"))
            CWorld::Players()[0].PlayerPed->GetMatrix().Position = pos;

        ImGui::End();
    }

private:
    int id = 0;
    CVector pos;
};

extern "C" jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    using namespace Luna;
    using namespace Luna::Game;

    auto logger = spdlog::android_logger_mt("luna", "luna");
    logger->set_level(spdlog::level::debug);

    spdlog::set_default_logger(logger);

    spdlog::info(
        "Luna, version: {}.{}.{}",
        LUNA_VERSION_MAJOR, LUNA_VERSION_MINOR, LUNA_VERSION_PATCH);

    CMod::Initialise();
    CGui::GetInstance().Subscribe(new DebugMenu);

    return JNI_VERSION_1_4;
}
