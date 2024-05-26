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

static void* libGTASAHandle = nullptr;

static void GetGameAddress() {
    static void* libGTASAHandle = nullptr;

    assert(libGTASAHandle == nullptr);

    libGTASAHandle = dlopen("libGTASA.so", RTLD_NOLOAD);

    if (libGTASAHandle == nullptr)
        spdlog::error("'libGTASA.so' not found!");

    // Calculate the game address.
    GameAddress = reinterpret_cast<uint8_t*>(dlsym(libGTASAHandle, "RwEngineInstance"));
    GameAddress -= 0x6CCD38;
}

void Game::InitialiseLuna() {
    GetGameAddress();

    // Remove write protection.

    // .data
    ModifyMemoryProtection(GameAddress + 0x67A000, 0x6B2D84 - 0x67A000, PROTECTION_READ | PROTECTION_WRITE);

    // .got
    ModifyMemoryProtection(GameAddress + 0x66E4D0, 0x679FF3 - 0x66E4D0, PROTECTION_READ | PROTECTION_WRITE);

    // .bss
    ModifyMemoryProtection(GameAddress + 0x6B2DC0, 0xA98FEF - 0x6B2DC0, PROTECTION_READ | PROTECTION_WRITE);

    // .text
    ModifyMemoryProtection(GameAddress + 0x1A1780, 0x5E84E7 - 0x1A1780, PROTECTION_READ | PROTECTION_WRITE | PROTECTION_EXEC);

    CGame::InitialiseLuna();
    CHud::InitialiseLuna();
    CPad::InitialiseLuna();
    CPlayerPed::InitialiseLuna();
    CRenderWare::InitialiseLuna();
    OSEvents::InitialiseLuna();
    CWorld::InitialiseLuna();

    CGui::Create().Initialise();
}
