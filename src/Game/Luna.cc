// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

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

void Game::InitializeGame() {
    CGame::InitializeLuna();
    CHud::InitializeLuna();
    CPad::InitializeLuna();
    CPlayerPed::InitializeLuna();
    CRenderWare::InitializeLuna();
    OSEvents::InitializeLuna();
    CWorld::InitializeLuna();

    CGui::Initialize();
}
