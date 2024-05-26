// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/Pad.hh>
#include <Luna/Game/Common.hh>
#include <Luna/Core/MemoryExec.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

CPad* CPad::LocalPad = nullptr;
CPad* CPad::CurrentPad = nullptr;

static struct {
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetPedWalkLeftRight;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetPedWalkUpDown;
    CFunction<bool (LUNA_THISCALL *)(CSAPad*)> GetSprint;
    CFunction<bool (LUNA_THISCALL *)(CSAPad*)> GetJump;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> JumpJustDown;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetAutoClimb;
    CFunction<bool (LUNA_THISCALL *)(CSAPad*)> DiveJustDown;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> SwimJumpJustDown;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> MeleeAttackJustDown;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetAbortClimb;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> DuckJustDown;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetBlock;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetSteeringLeftRight;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetSteeringUpDown;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetAccelerate;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetBrake;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetHandBrake;
    CFunction<int (LUNA_THISCALL *)(CSAPad*)> GetHorn;
    // CFunction<int (LUNA_THISCALL *)(CSAPad*, bool, void*, bool, void const*)> ExitVehicleJustDown;
} trampoline;

static LUNA_THISCALL int hook_GetPedWalkLeftRight(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->LeftRight = trampoline.GetPedWalkLeftRight(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int hook_GetPedWalkUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = trampoline.GetPedWalkUpDown(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL bool hook_GetSprint(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = trampoline.GetSprint(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT);
}

static LUNA_THISCALL bool hook_GetJump(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = trampoline.GetJump(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int hook_JumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.JumpJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int hook_GetAutoClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetAutoClimb(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static bool LUNA_THISCALL hook_DiveJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        bool val = trampoline.DiveJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int hook_SwimJumpJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.SwimJumpJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP);
}

static LUNA_THISCALL int hook_MeleeAttackJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.MeleeAttackJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int hook_GetAbortClimb(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetAbortClimb(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SECONDARY_ATTACK;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SECONDARY_ATTACK);
}

static LUNA_THISCALL int hook_DuckJustDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.DuckJustDown(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_CROUCH;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_CROUCH);
}

static LUNA_THISCALL int hook_GetBlock(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetBlock(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_HANDBRAKE;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_HANDBRAKE);
}

static LUNA_THISCALL int hook_GetSteeringLeftRight(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->LeftRight = trampoline.GetSteeringLeftRight(self);

    return CPad::CurrentPad->LeftRight;
}

static LUNA_THISCALL int hook_GetSteeringUpDown(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad)
        CPad::CurrentPad->UpDown = trampoline.GetSteeringUpDown(self);

    return CPad::CurrentPad->UpDown;
}

static LUNA_THISCALL int hook_GetAccelerate(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetAccelerate(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_SPRINT;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_SPRINT) ? 0xFF : 0;
}

static LUNA_THISCALL int hook_GetBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetBrake(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_JUMP;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_JUMP) ? 0xFF : 0;
}

static LUNA_THISCALL int hook_GetHandBrake(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetHandBrake(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_HANDBRAKE;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_HANDBRAKE) ? 0xFF : 0;
}

static LUNA_THISCALL int hook_GetHorn(CSAPad* self) {
    if (CPad::CurrentPad == CPad::LocalPad) {
        int val = trampoline.GetHorn(self);

        if (val)
            CPad::CurrentPad->Keys |= PAD_KEY_CROUCH;

        return val;
    }

    return CPad::CurrentPad->IsKeyPressed(PAD_KEY_CROUCH);
}

// static LUNA_THISCALL int hook_ExitVehicleJustDown(CSAPad* self, bool param1, void* param2, bool param3, void const* param4) {
//     if (CPad::CurrentPad == CPad::LocalPad)
//         return trampoline.ExitVehicleJustDown(self, param1, param2, param3, param4);

//     return 0;
// }

void CPad::InitialiseLuna() {
    // trampoline.MeleeAttackJustDown.Allocate(10 + ABS_JUMP_SIZE);
    trampoline.GetBlock.Allocate(12 + ABS_JUMP_SIZE);

    // memcpy(
    //     trampoline.MeleeAttackJustDown.Code(),
    //     GameAddress + 0x40B00D,
    //     10
    // );

    // MakeAbsJump(
    //     trampoline.MeleeAttackJustDown.Code() + 10,
    //     GameAddress + 0x40B016,
    //     true
    // );

    *reinterpret_cast<uint32_t*>(trampoline.GetBlock.Code()) = 0x466FB580;

    // ldr.w lr, [pc, #0]
    *reinterpret_cast<uint32_t*>(trampoline.GetBlock.Code() + 4) = 0xE000F8DF;
    *reinterpret_cast<uint8_t**>(trampoline.GetBlock.Code() + 8) = GameAddress + 0x40B329;

    MakeAbsJump(
        trampoline.GetBlock.Code() + 12,
        GameAddress + 0x29CC74,
        true
    );

    MakeHook(&trampoline.GetPedWalkLeftRight, GameAddress + 0x40A219, hook_GetPedWalkLeftRight);
    MakeHook(&trampoline.GetPedWalkUpDown, GameAddress + 0x40A299, hook_GetPedWalkUpDown);
    MakeHook(&trampoline.GetSprint, GameAddress + 0x40BDB1, hook_GetSprint);
    MakeHook(&trampoline.GetJump, GameAddress + 0x40BC59, hook_GetJump);
    MakeHook(&trampoline.JumpJustDown, GameAddress + 0x40BCAD, hook_JumpJustDown);
    MakeHook(&trampoline.GetAutoClimb, GameAddress + 0x40BB0D, hook_GetAutoClimb);
    MakeHook(&trampoline.DiveJustDown, GameAddress + 0x40BD11, hook_DiveJustDown);
    // MakeHook(&trampoline.SwimJumpJustDown, GameAddress + 0x40BD59, hook_SwimJumpJustDown);
    MakeHook(nullptr, GameAddress + 0x40B00D, hook_MeleeAttackJustDown);
    MakeHook(&trampoline.GetAbortClimb, GameAddress + 0x40BBB9, hook_GetAbortClimb);
    MakeHook(&trampoline.DuckJustDown, GameAddress + 0x40BA9D, hook_DuckJustDown);
    MakeHook(nullptr, GameAddress + 0x40B321, hook_GetBlock);
    MakeHook(&trampoline.GetSteeringLeftRight, GameAddress + 0x409B55, hook_GetSteeringLeftRight);
    MakeHook(&trampoline.GetSteeringUpDown, GameAddress + 0x409D25, hook_GetSteeringUpDown);
    MakeHook(&trampoline.GetAccelerate, GameAddress + 0x40B351, hook_GetAccelerate);
    MakeHook(&trampoline.GetBrake, GameAddress + 0x40A9AD, hook_GetBrake);
    MakeHook(&trampoline.GetHandBrake, GameAddress + 0x40A7E1, hook_GetHandBrake);
    MakeHook(&trampoline.GetHorn, GameAddress + 0x40A619, hook_GetHorn);
    // MakeHook(&trampoline.ExitVehicleJustDown, GameAddress + 0x40AA7D, hook_ExitVehicleJustDown);

    // Our implementation of function hooking is very basic and
    // some functions can be problematic, so we will have to manually implement the hooks
    // for these functions.


}
