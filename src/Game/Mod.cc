// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Mod.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Game/Game.hh>
#include <Luna/Game/Gui.hh>
#include <Luna/Game/Hud.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/RW.hh>
#include <Luna/Game/OSEvent.hh>
#include <Luna/Game/World.hh>
#include <Luna/Utils/Memory.hh>

#include <spdlog/spdlog.h>
#include <dlfcn.h>

using namespace Luna;
using namespace Luna::Game;
using namespace Luna::Utils;

uint8_t* Game::GameAddress = nullptr;

static void GetGameAddress() {
    void* libGTASAHandle = dlopen("libGTASA.so", RTLD_NOLOAD);

    if (libGTASAHandle == nullptr)
        spdlog::error("'libGTASA.so' not found!");

    // Calculate the game address.
    GameAddress = reinterpret_cast<uint8_t*>(dlsym(libGTASAHandle, "RwEngineInstance"));
    GameAddress -= 0x6CCD38;
}

void CMod::Initialise() {
    GetGameAddress();

    // Remove write protection.

    // .data
    ModifyMemoryProtection(GameAddress + 0x67A000, 0x6B2D84 - 0x67A000, PROTECTION_READ | PROTECTION_WRITE);

    // .got
    ModifyMemoryProtection(GameAddress + 0x66E4D8, 0x679FF7 - 0x66E4D8, PROTECTION_READ | PROTECTION_WRITE);

    // .bss
    ModifyMemoryProtection(GameAddress + 0x6B2DC0, 0xA98FEF - 0x6B2DC0, PROTECTION_READ | PROTECTION_WRITE);

    CGameMod::Install();
    CHudMod::Install();
    CPadMod::Install();
    CPlayerPedMod::Install();
    CRenderWareMod::Install();
    OSEventsMod::Install();
    CWorldMod::Install();

    CGui::Create().Initialise();
}
