// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

// #include <cstdint>

namespace Luna::Game {
    class CHud {
    public:
        static void InitialiseLuna();

        CHud() = delete;
        ~CHud() = delete;

        void DrawAfterFade();
    };
}
