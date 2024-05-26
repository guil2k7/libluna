// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Pad.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Core/Hook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

CPad* CPad::LocalPad = nullptr;
CPad* CPad::CurrentPad = nullptr;

static struct {
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetPedWalkLeftRight;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetPedWalkUpDown;
    CHook<bool (LUNA_THISCALL *)(CSAPad*)> GetSprint;
    CHook<bool (LUNA_THISCALL *)(CSAPad*)> GetJump;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> JumpJustDown;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetAutoClimb;
    CHook<bool (LUNA_THISCALL *)(CSAPad*)> DiveJustDown;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> SwimJumpJustDown;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> MeleeAttackJustDown;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetAbortClimb;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> DuckJustDown;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetBlock;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetSteeringLeftRight;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetSteeringUpDown;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetAccelerate;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetBrake;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetHandBrake;
    CHook<int (LUNA_THISCALL *)(CSAPad*)> GetHorn;
    // CHook<int (LUNA_THISCALL *)(CSAPad*, bool, void*, bool, void const*)> ExitVehicleJustDown;
} hook;

static LUNA_THISCALL int GetPedWalkLeftRight(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->LeftRight = hook.GetPedWalkLeftRight.Trampoline()(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int GetPedWalkUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = hook.GetPedWalkUpDown.Trampoline()(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL bool GetSprint(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = hook.GetSprint.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT);
}

static LUNA_THISCALL bool GetJump(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = hook.GetJump.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int JumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.JumpJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int GetAutoClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetAutoClimb.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static bool LUNA_THISCALL DiveJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = hook.DiveJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int SwimJumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.SwimJumpJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int MeleeAttackJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.MeleeAttackJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int GetAbortClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetAbortClimb.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int DuckJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.DuckJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_CROUCH;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_CROUCH);
}

static LUNA_THISCALL int GetBlock(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetBlock.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_HANDBRAKE;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_HANDBRAKE);
}

static LUNA_THISCALL int GetSteeringLeftRight(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->LeftRight = hook.GetSteeringLeftRight.Trampoline()(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int GetSteeringUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = hook.GetSteeringUpDown.Trampoline()(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL int GetAccelerate(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetAccelerate.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT) ? 0xFF : 0;
}

static LUNA_THISCALL int GetBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetBrake.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP) ? 0xFF : 0;
}

static LUNA_THISCALL int GetHandBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetHandBrake.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_HANDBRAKE;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_HANDBRAKE) ? 0xFF : 0;
}

static LUNA_THISCALL int GetHorn(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetHorn.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_CROUCH;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_CROUCH);
}

// static LUNA_THISCALL int ExitVehicleJustDown(CSAPad* self, bool param1, void* param2, bool param3, void const* param4) {
//     if (CPad::CurrentPad == CPad::LocalPad)
//         return hook.ExitVehicleJustDown.Trampoline()(self, param1, param2, param3, param4);

//     return 0;
// }

void CPad::InitialiseLuna() {
    hook.GetPedWalkLeftRight.Hook(GameAddress + 0x40A219, GetPedWalkLeftRight);
    hook.GetPedWalkUpDown.Hook(GameAddress + 0x40A299, GetPedWalkUpDown);
    hook.GetSprint.Hook(GameAddress + 0x40BDB1, GetSprint);
    hook.GetJump.Hook(GameAddress + 0x40BC59, GetJump);
    hook.JumpJustDown.Hook(GameAddress + 0x40BCAD, JumpJustDown);
    hook.GetAutoClimb.Hook(GameAddress + 0x40BB0D, GetAutoClimb);
    hook.DiveJustDown.Hook(GameAddress + 0x40BD11, DiveJustDown);
    hook.SwimJumpJustDown.Hook(GameAddress + 0x40BD59, SwimJumpJustDown);
    hook.MeleeAttackJustDown.Hook(GameAddress + 0x40B00D, MeleeAttackJustDown);
    hook.GetAbortClimb.Hook(GameAddress + 0x40BBB9, GetAbortClimb);
    hook.DuckJustDown.Hook(GameAddress + 0x40BA9D, DuckJustDown);
    // hook.GetBlock.Hook(GameAddress + 0x40B321, GetBlock);
    hook.GetSteeringLeftRight.Hook(GameAddress + 0x409B55, GetSteeringLeftRight);
    hook.GetSteeringUpDown.Hook(GameAddress + 0x409D25, GetSteeringUpDown);
    hook.GetAccelerate.Hook(GameAddress + 0x40B351, GetAccelerate);
    hook.GetBrake.Hook(GameAddress + 0x40A9AD, GetBrake);
    hook.GetHandBrake.Hook(GameAddress + 0x40A7E1, GetHandBrake);
    hook.GetHorn.Hook(GameAddress + 0x40A619, GetHorn);
    // hook.ExitVehicleJustDown.Hook(GameAddress + 0x40AA7D, ExitVehicleJustDown);
}
