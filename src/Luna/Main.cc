// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include "Luna/Game/PlayerPed.hh"
#include <Luna/Core/Memory.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Game/imgui_impl_rw.hh>
#include <Luna/Game/Luna.hh>
#include <Luna/Game/World.hh>
#include <Luna/Network/Client.hh>
#include <Luna/Network/LocalPlayer.hh>
#include <Luna/Network/RemotePlayer.hh>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/android_sink.h>
#include <jni.h>
#include <dlfcn.h>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;
using namespace Luna::Network;

class DebugMenu final : public IGuiWidget {
public:
    DebugMenu() {
        strcpy(host, "192.168.1.14");
    }

    void Render() {
        ImGui::Begin("Debug Menu");

        ImGui::InputText("IP or Host", host, sizeof host);

        if (ImGui::Button("Connect")) {
            CConnectionParams connectionParams;

            connectionParams.Nickname = "LunaMultiplayer";
            connectionParams.Host = std::string_view(host);
            connectionParams.Port = 7777;

            client->SetConnectionParams(connectionParams);
            client->Connect();
        }

        if (!gameMenu) {
            if (ImGui::Button("In Game?"))
                gameMenu = true;
        }
        else {
            RenderGameMenu();
        }

        ImGui::End();
    }

    void RenderGameMenu() {
        CPlayerPed* mainPlayer = CWorld::GetPlayerPed();

        ImGui::Text("Health: %.3f", mainPlayer->Health());

        if (ImGui::Button("Kill"))
            mainPlayer->SetHealth(0.0f);
    }

private:
    int id = 0;
    bool gameMenu = false;
    char host[128];
};


static void* libGTASAHandle = nullptr;

static void CalcGameAddress() {
    libGTASAHandle = dlopen("libGTASA.so", RTLD_NOLOAD);

    if (libGTASAHandle == nullptr)
        spdlog::error("'libGTASA.so' not found!");

    // Calculate the game address.
    GameAddress
        = reinterpret_cast<uint8_t*>(dlsym(libGTASAHandle, "RwEngineInstance"))
        - 0x6CCD38;
}

static void RemoveWriteProtections() {
    // .data
    ModifyMemoryProtection(GameAddress + 0x67A000, 0x6B2D84 - 0x67A000, PROTECTION_READ | PROTECTION_WRITE);

    // .got
    ModifyMemoryProtection(GameAddress + 0x66E4D0, 0x679FF3 - 0x66E4D0, PROTECTION_READ | PROTECTION_WRITE);

    // .bss
    ModifyMemoryProtection(GameAddress + 0x6B2DC0, 0xA98FEF - 0x6B2DC0, PROTECTION_READ | PROTECTION_WRITE);

    // .text
    ModifyMemoryProtection(GameAddress + 0x1A1780, 0x5E84E7 - 0x1A1780, PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC);
}

static void Initialize() {
    CalcGameAddress();
    RemoveWriteProtections();

    client = new CClient();

    CRemotePlayerComponent* remotePlayerComponent = new CRemotePlayerComponent;
    remotePlayerComponent->Install(*client);

    CLocalPlayerComponent* localPlayerComponent = new CLocalPlayerComponent;
    localPlayerComponent->Install(*client);

    InitializeGame();

    CGui::Instance().Subscribe(new DebugMenu());
}

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    auto logger = spdlog::android_logger_mt("luna", "luna");
    logger->set_level(spdlog::level::debug);

    spdlog::set_default_logger(logger);

    spdlog::info("Luna!!!");
    spdlog::info("  Version: {}.{}.{}", LUNA_VERSION_MAJOR, LUNA_VERSION_MINOR, LUNA_VERSION_PATCH);

    Initialize();

    return JNI_VERSION_1_4;
}
