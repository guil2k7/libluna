// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Task.hh"
#include "../Common.hh"

namespace Luna::Game {

class CTaskComplexDie : public CTask {
public:
    static CTaskComplexDie* Create(
        int weaponType = 0,
        int animGroup = 0,
        int animID = 15,
        float blendDelta = 4.0f,
        float animSpeed = 0.0f,
        bool beingKilledByStealth = false,
        bool fallingToDeath = false,
        int fallToDeathDir = 0,
        bool fallToDeathOverRailing = false
    );

private:
    PADDING(0x28);
};

VALIDATE_SIZE(CTaskComplexDie, 0x28);

inline CTaskComplexDie* CTaskComplexDie::Create(
    int weaponType, int animGroup, int animID,
    float blendDelta, float animSpeed,
    bool beingKilledByStealth, bool fallingToDeath,
    int fallToDeathDir, bool fallToDeathOverRailing
) {
    auto self = CTask::operator new(sizeof (CTaskComplexDie));

    // Constructor.
    CallMethod<void*, int, int, int, float, float, bool, bool, int, bool>(
        GameAddress + 0x4FB5E1, self,
        weaponType, animGroup, animID, blendDelta, animSpeed,
        beingKilledByStealth, fallingToDeath, fallToDeathDir, fallingToDeath
    );

    return reinterpret_cast<CTaskComplexDie*>(self);
}

} // namespace Luna::Game
