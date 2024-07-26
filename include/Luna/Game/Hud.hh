// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

namespace Luna::Game {

class CHud {
public:
    static void InitializeLuna();

    CHud() = delete;
    ~CHud() = delete;

    void DrawAfterFade();
};

} // namespce Luna::Game
