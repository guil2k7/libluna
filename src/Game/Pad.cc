// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Game/Pad.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Core/Hooker.hh>
#include <Luna/Core/Hooker.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

CPad* CPad::LocalPad = nullptr;
CPad* CPad::CurrentPad = nullptr;

static struct {
    int (LUNA_THISCALL *GetPedWalkLeftRight)(CSAPad*);
    int (LUNA_THISCALL *GetPedWalkUpDown)(CSAPad*);
    bool (LUNA_THISCALL *GetSprint)(CSAPad*);
    bool (LUNA_THISCALL *GetJump)(CSAPad*);
    int (LUNA_THISCALL *JumpJustDown)(CSAPad*);
    int (LUNA_THISCALL *GetAutoClimb)(CSAPad*);
    bool (LUNA_THISCALL *DiveJustDown)(CSAPad*);
    int (LUNA_THISCALL *SwimJumpJustDown)(CSAPad*);
    int (LUNA_THISCALL *MeleeAttackJustDown)(CSAPad*);
    int (LUNA_THISCALL *GetAbortClimb)(CSAPad*);
    int (LUNA_THISCALL *DuckJustDown)(CSAPad*);
    int (LUNA_THISCALL *GetBlock)(CSAPad*);
    int (LUNA_THISCALL *GetSteeringLeftRight)(CSAPad*);
    int (LUNA_THISCALL *GetSteeringUpDown)(CSAPad*);
    int (LUNA_THISCALL *GetAccelerate)(CSAPad*);
    int (LUNA_THISCALL *GetBrake)(CSAPad*);
    int (LUNA_THISCALL *GetHandBrake)(CSAPad*);
    int (LUNA_THISCALL *GetHorn)(CSAPad*);
    int (LUNA_THISCALL *ExitVehicleJustDown)(CSAPad*, bool, void*, bool, void const*);
} trampoline;

static LUNA_THISCALL int HookImpl_GetPedWalkLeftRight(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->LeftRight = trampoline.GetPedWalkLeftRight(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int HookImpl_GetPedWalkUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = trampoline.GetPedWalkUpDown(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL bool HookImpl_GetSprint(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = trampoline.GetSprint(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT);
}

static LUNA_THISCALL bool HookImpl_GetJump(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = trampoline.GetJump(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int HookImpl_JumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.JumpJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int HookImpl_GetAutoClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetAutoClimb(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static bool LUNA_THISCALL HookImpl_DiveJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = trampoline.DiveJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int HookImpl_SwimJumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.SwimJumpJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int HookImpl_MeleeAttackJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = CallFunction<int>(GameAddress + 0x40B00D, self);        
        // int val = trampoline.MeleeAttackJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int HookImpl_GetAbortClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetAbortClimb(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int HookImpl_DuckJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.DuckJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_CROUCH;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_CROUCH);
}

static LUNA_THISCALL int HookImpl_GetBlock(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = CallFunction<int>(GameAddress + 0x40B321, self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_HANDBRAKE;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_HANDBRAKE);
}

static LUNA_THISCALL int HookImpl_GetSteeringLeftRight(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->LeftRight = trampoline.GetSteeringLeftRight(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int HookImpl_GetSteeringUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = trampoline.GetSteeringUpDown(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL int HookImpl_GetAccelerate(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetAccelerate(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT) ? 0xFF : 0;
}

static LUNA_THISCALL int HookImpl_GetBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetBrake(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP) ? 0xFF : 0;
}

static LUNA_THISCALL int HookImpl_GetHandBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetHandBrake(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_HANDBRAKE;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_HANDBRAKE) ? 0xFF : 0;
}

static LUNA_THISCALL int HookImpl_GetHorn(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetHorn(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_CROUCH;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_CROUCH);
}

static LUNA_THISCALL int HookImpl_ExitVehicleJustDown(CSAPad* self, bool param1, void* param2, bool param3, void const* param4) {
    if (CPad::CurrentPad == CPad::LocalPad)
        return trampoline.ExitVehicleJustDown(self, param1, param2, param3, param4);

    return 0;
}

void CPad::InitializeLuna() {
    trampoline.GetPedWalkLeftRight = CHooker(GameAddress + 0x40A219, HookImpl_GetPedWalkLeftRight, true).Hook();
    trampoline.GetPedWalkUpDown = CHooker(GameAddress + 0x40A299, HookImpl_GetPedWalkUpDown, true).Hook();
    trampoline.GetSprint = CHooker(GameAddress + 0x40BDB1, HookImpl_GetSprint, true).Hook();
    trampoline.GetJump = CHooker(GameAddress + 0x40BC59, HookImpl_GetJump, true).Hook();
    trampoline.JumpJustDown = CHooker(GameAddress + 0x40BCAD, HookImpl_JumpJustDown, true).Hook();
    trampoline.GetAutoClimb = CHooker(GameAddress + 0x40BB0D, HookImpl_GetAutoClimb, true).Hook();
    trampoline.DiveJustDown = CHooker(GameAddress + 0x40BD11, HookImpl_DiveJustDown, true).Hook();
    trampoline.SwimJumpJustDown = CHooker(GameAddress + 0x40BD59, HookImpl_SwimJumpJustDown, true).Hook();
    trampoline.MeleeAttackJustDown = CHooker(GameAddress + 0x1A2AB0, HookImpl_MeleeAttackJustDown, true).Hook();
    trampoline.GetAbortClimb = CHooker(GameAddress + 0x40BBB9, HookImpl_GetAbortClimb, true).Hook();
    trampoline.DuckJustDown = CHooker(GameAddress + 0x40BA9D, HookImpl_DuckJustDown, true).Hook();
    trampoline.GetBlock = CHooker(GameAddress + 0x19E0FC, HookImpl_GetBlock, true).Hook();
    trampoline.GetSteeringLeftRight = CHooker(GameAddress + 0x409B55, HookImpl_GetSteeringLeftRight, true).Hook();
    trampoline.GetSteeringUpDown = CHooker(GameAddress + 0x409D25, HookImpl_GetSteeringUpDown, true).Hook();
    trampoline.GetAccelerate = CHooker(GameAddress + 0x40B351, HookImpl_GetAccelerate, true).Hook();
    trampoline.GetBrake = CHooker(GameAddress + 0x40A9AD, HookImpl_GetBrake, true).Hook();
    trampoline.GetHandBrake = CHooker(GameAddress + 0x40A7E1, HookImpl_GetHandBrake, true).Hook();
    trampoline.GetHorn = CHooker(GameAddress + 0x40A619, HookImpl_GetHorn, true).Hook();
    trampoline.ExitVehicleJustDown = CHooker(GameAddress + 0x40AA7D, HookImpl_ExitVehicleJustDown, true).Hook();
}
