// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "PlayerInfo.hh"

namespace Luna::Game {
    class CWorld {
    public:
        static void InitialiseLuna();

        CWorld() = delete;
        ~CWorld() = delete;

        inline static CPlayerInfo* Players() {
            return *reinterpret_cast<CPlayerInfo**>(GameAddress + 0x6883C0);
        }
    };
}
