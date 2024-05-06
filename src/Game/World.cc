// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/World.hh>
#include <Luna/Game/Common.hh>

using namespace Luna;
using namespace Luna::Game;

void CWorldMod::Install() {
    *reinterpret_cast<CPlayerInfo**>(GameAddress + 0x6883C8)
        = reinterpret_cast<CPlayerInfo*>(::operator new(sizeof (CPlayerInfo) * 1024));
}
