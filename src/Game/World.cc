// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/World.hh>
#include <Luna/Game/Common.hh>

using namespace Luna;
using namespace Luna::Game;

void CWorld::InitialiseLuna() {
    *reinterpret_cast<CPlayerInfo**>(GameAddress + 0x6883C0)
        = reinterpret_cast<CPlayerInfo*>(::operator new(sizeof (CPlayerInfo) * 1024));
}
