// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "PlayerInfo.hh"

namespace Luna::Game {
    class CWorld {
    public:
        CWorld() = delete;
        ~CWorld() = delete;

        inline static CPlayerInfo* Players() {
            return *reinterpret_cast<CPlayerInfo**>(GameAddress + 0x6883C8);
        }

        inline static uint8_t& PlayerInFocus() {
            return *reinterpret_cast<uint8_t*>(GameAddress + 0x97B9C4);
        }
    };

    class CWorldMod {
    public:
        static void Install();
    };
}
