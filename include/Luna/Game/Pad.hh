// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Common.hh"

namespace Luna::Game {
    class CPad {
    public:
        static inline CPad* GetPads() {
            return *reinterpret_cast<CPad**>(GameAddress + 0x687B14);
        }

        static inline CPad* GetPad(int id) {
            return &GetPads()[id];
        }

        inline CPad() {
            Clear(true, true);
        }

        inline void Clear(bool enablePlayerControls, bool resetPhase) {
            CallMethod<void, bool, bool>(
                GameAddress + 0x408131, this, enablePlayerControls, resetPhase);
        }

        static int MapPad1To;

    private:
        PADDING(0x158);
    };

    VALIDATE_SIZE(CPad, 0x158);

    class CPadMod {
    public:
        static void Install();
    };
}
