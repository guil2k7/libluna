// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Gui.hh>
#include <Luna/Game/imgui_impl_rw.hh>
#include <Luna/Game/Luna.hh>
#include <Luna/Network/Client.hh>
#include <Luna/Network/RemotePlayer.hh>

#include <jni.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/android_sink.h>

using namespace Luna;
using namespace Luna::Game;
using namespace Luna::Network;

class DebugMenu final : public IGuiWidget {
public:
    DebugMenu() {
        strcpy(host, "192.168.1.14");
    }

    void Render() {
        ImGui::Begin("Debug Menu");

        ImGui::SliderInt("ID", &id, 0, 1000);

        if (ImGui::Button("<<"))
            id -= 1;

        ImGui::SameLine();

        if (ImGui::Button(">>"))
            id += 1;

        ImGui::InputText("IP or Host", host, sizeof host);

        if (ImGui::Button("Connect")) {
            CConnectionParams connectionParams;

            connectionParams.Nickname = "guil2k7_luna";
            connectionParams.Host = std::string_view(host);
            connectionParams.Port = 7777;

            client->SetConnectionParams(connectionParams);
            client->Connect();
        }

        ImGui::End();
    }

private:
    int id = 0;
    char host[128];
};

extern "C" __attribute__((visibility("default"))) void LunaInitialize(void* libGTASAHandle) {
    client = new CClient();

    CRemotePlayerComponent* remotePlayerComponent = new CRemotePlayerComponent;
    remotePlayerComponent->Install(*client);

    InitializeGame(libGTASAHandle);
}
