// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

// #include <cstdint>

namespace Luna::Game {
    class CHud {
    public:
        CHud() = delete;

        void DrawAfterFade();
    };

    class CHudMod {
    public:
        static void Install();
    };
}
