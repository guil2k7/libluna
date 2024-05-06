// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Common.hh"

namespace Luna::Game {
    class CPlayerPed;

    class CPlayerInfo {
    public:
        CPlayerPed* PlayerPed;

    private:
        PADDING(0x190);
    };

    VALIDATE_SIZE(CPlayerInfo, 0x194);
}
