// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Luna.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Game.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Game/Hud.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/RW.hh>
#include <Luna/Game/OSEvent.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/Memory.hh>

#include <spdlog/spdlog.h>
#include <dlfcn.h>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

uint8_t* Game::GameAddress = nullptr;

void Game::InitializeGame(void* libGTASAHandle) {
    GameAddress
        = reinterpret_cast<uint8_t*>(dlsym(libGTASAHandle, "RwEngineInstance"))
        - 0x6CCD38;

    CGame::InitializeLuna();
    CHud::InitializeLuna();
    CPad::InitializeLuna();
    CPlayerPed::InitializeLuna();
    CRenderWare::InitializeLuna();
    OSEvents::InitializeLuna();
    CWorld::InitializeLuna();

    CGui::Create().Initialize();
}
