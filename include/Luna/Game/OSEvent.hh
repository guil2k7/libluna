// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

namespace Luna::Game {
    enum eTouchAction : int {
        TOUCH_ACTION_RELEASE = 1,
        TOUCH_ACTION_PRESS,
        TOUCH_ACTION_MOVE,
    };

    class OSEvents {
    public:
        static void InitialiseLuna();

        static void ShowKeyboard();
        static void HideKeyboard();
        static bool IsKeyboardShown();
    };
}
