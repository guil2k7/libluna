// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Pad.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Core/ThumbHook.hh>
#include <Luna/Core/ArmHook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

CPad* CPad::LocalPad = nullptr;
CPad* CPad::CurrentPad = nullptr;

static struct {
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetPedWalkLeftRight;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetPedWalkUpDown;
    CThumbHook<bool (LUNA_THISCALL *)(CSAPad*)> GetSprint;
    CThumbHook<bool (LUNA_THISCALL *)(CSAPad*)> GetJump;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> JumpJustDown;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetAutoClimb;
    CThumbHook<bool (LUNA_THISCALL *)(CSAPad*)> DiveJustDown;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> SwimJumpJustDown;
    CArmHook<int (LUNA_THISCALL *)(CSAPad*)> MeleeAttackJustDown;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetAbortClimb;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> DuckJustDown;
    CArmHook<int (LUNA_THISCALL *)(CSAPad*)> GetBlock;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetSteeringLeftRight;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetSteeringUpDown;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetAccelerate;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetBrake;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetHandBrake;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*)> GetHorn;
    CThumbHook<int (LUNA_THISCALL *)(CSAPad*, bool, void*, bool, void const*)> ExitVehicleJustDown;
} hook;

static LUNA_THISCALL int HookImpl_GetPedWalkLeftRight(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->LeftRight = hook.GetPedWalkLeftRight.Trampoline()(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int HookImpl_GetPedWalkUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = hook.GetPedWalkUpDown.Trampoline()(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL bool HookImpl_GetSprint(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = hook.GetSprint.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT);
}

static LUNA_THISCALL bool HookImpl_GetJump(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = hook.GetJump.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int HookImpl_JumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.JumpJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int HookImpl_GetAutoClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetAutoClimb.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static bool LUNA_THISCALL HookImpl_DiveJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = hook.DiveJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int HookImpl_SwimJumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.SwimJumpJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int HookImpl_MeleeAttackJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = CallFunction<int>(GameAddress + 0x40B00D, self);        
        // int val = hook.MeleeAttackJustDown.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int HookImpl_GetAbortClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetAbortClimb.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int HookImpl_DuckJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.DuckJustDown.Trampoline()(self);

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
        CPad::CurrentPad->LeftRight = hook.GetSteeringLeftRight.Trampoline()(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int HookImpl_GetSteeringUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = hook.GetSteeringUpDown.Trampoline()(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL int HookImpl_GetAccelerate(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetAccelerate.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT) ? 0xFF : 0;
}

static LUNA_THISCALL int HookImpl_GetBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetBrake.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP) ? 0xFF : 0;
}

static LUNA_THISCALL int HookImpl_GetHandBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetHandBrake.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_HANDBRAKE;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_HANDBRAKE) ? 0xFF : 0;
}

static LUNA_THISCALL int HookImpl_GetHorn(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = hook.GetHorn.Trampoline()(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_CROUCH;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_CROUCH);
}

static LUNA_THISCALL int HookImpl_ExitVehicleJustDown(CSAPad* self, bool param1, void* param2, bool param3, void const* param4) {
    if (CPad::CurrentPad == CPad::LocalPad)
        return hook.ExitVehicleJustDown.Trampoline()(self, param1, param2, param3, param4);

    return 0;
}

void CPad::InitializeLuna() {
    hook.GetPedWalkLeftRight.Hook(GameAddress + 0x40A219, HookImpl_GetPedWalkLeftRight);
    hook.GetPedWalkUpDown.Hook(GameAddress + 0x40A299, HookImpl_GetPedWalkUpDown);
    hook.GetSprint.Hook(GameAddress + 0x40BDB1, HookImpl_GetSprint);
    hook.GetJump.Hook(GameAddress + 0x40BC59, HookImpl_GetJump);
    hook.JumpJustDown.Hook(GameAddress + 0x40BCAD, HookImpl_JumpJustDown);
    hook.GetAutoClimb.Hook(GameAddress + 0x40BB0D, HookImpl_GetAutoClimb);
    hook.DiveJustDown.Hook(GameAddress + 0x40BD11, HookImpl_DiveJustDown);
    hook.SwimJumpJustDown.Hook(GameAddress + 0x40BD59, HookImpl_SwimJumpJustDown);
    hook.MeleeAttackJustDown.Hook(GameAddress + 0x1A2AB0, HookImpl_MeleeAttackJustDown);
    hook.GetAbortClimb.Hook(GameAddress + 0x40BBB9, HookImpl_GetAbortClimb);
    hook.DuckJustDown.Hook(GameAddress + 0x40BA9D, HookImpl_DuckJustDown);
    hook.GetBlock.Hook(GameAddress + 0x19E0FC, HookImpl_GetBlock);
    hook.GetSteeringLeftRight.Hook(GameAddress + 0x409B55, HookImpl_GetSteeringLeftRight);
    hook.GetSteeringUpDown.Hook(GameAddress + 0x409D25, HookImpl_GetSteeringUpDown);
    hook.GetAccelerate.Hook(GameAddress + 0x40B351, HookImpl_GetAccelerate);
    hook.GetBrake.Hook(GameAddress + 0x40A9AD, HookImpl_GetBrake);
    hook.GetHandBrake.Hook(GameAddress + 0x40A7E1, HookImpl_GetHandBrake);
    hook.GetHorn.Hook(GameAddress + 0x40A619, HookImpl_GetHorn);
    hook.ExitVehicleJustDown.Hook(GameAddress + 0x40AA7D, HookImpl_ExitVehicleJustDown);

    hook.GetPedWalkLeftRight.Activate();
    hook.GetPedWalkUpDown.Activate();
    hook.GetSprint.Activate();
    hook.GetJump.Activate();
    hook.JumpJustDown.Activate();
    hook.GetAutoClimb.Activate();
    hook.DiveJustDown.Activate();
    hook.SwimJumpJustDown.Activate();
    hook.MeleeAttackJustDown.Activate();
    hook.GetAbortClimb.Activate();
    hook.DuckJustDown.Activate();
    hook.GetBlock.Activate();
    hook.GetSteeringLeftRight.Activate();
    hook.GetSteeringUpDown.Activate();
    hook.GetAccelerate.Activate();
    hook.GetBrake.Activate();
    hook.GetHandBrake.Activate();
    hook.GetHorn.Activate();
    hook.ExitVehicleJustDown.Activate();
}
