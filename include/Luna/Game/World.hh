// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "PlayerInfo.hh"

namespace Luna::Game {
    
class CWorld {
public:
    static void InitializeLuna();

    CWorld() = delete;
    ~CWorld() = delete;

    static inline CPlayerInfo* Players() {
        return *reinterpret_cast<CPlayerInfo**>(GameAddress + 0x6883C0);
    }

    static inline CPlayerPed* GetPlayerPed(int id = 0) {
        return reinterpret_cast<CPlayerInfo**>(GameAddress + 0x6883C0)[id]->PlayerPed;
    }
};

} // namespce Luna::Game
