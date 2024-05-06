// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/Hook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static struct {
    /// CPlayerPed::SetupPlayerPed(int)
    CHook<void (LUNA_STDCALL *)(int)> SetupPlayerPed;

    /// CPlayerPed::CPlayerPed()
    CHook<CPlayerPed* (LUNA_THISCALL *)(CPlayerPed*, int, bool)> Constructor;

    /// CPlayerPed::ProcessControl()
    CHook<void (LUNA_THISCALL *)(CPlayerPed*)> ProcessControl;

    /// CPlayerPed::GetPadFromPlayer()
    CHook<CPad* (LUNA_THISCALL *)(CPlayerPed*)> GetPadFromPlayer;

    /// CPlayerPed::GetPadFromPlayer()
    CHook<CPlayerInfo* (LUNA_THISCALL *)(CPlayerPed*)> GetPlayerInfoForThisPlayerPed;
} hook;

void CPlayerPedMod::Install() {
    hook.SetupPlayerPed.Hook(
        GameAddress + 0x4D3935,
        CPlayerPed::SetupPlayerPed
    );

    hook.Constructor.Hook(
        GameAddress + 0x4D360D,
        CPlayerPed::InitialiseInstance
    );

    hook.ProcessControl.Hook(
        GameAddress + 0x4D4779,
        [](CPlayerPed* self) { return self->ProcessControl(); }
    );

    hook.GetPadFromPlayer.Hook(
        GameAddress + 0x4D46D9,
        [](CPlayerPed* self) { return CPad::GetPad(self->GetID()); }
    );

    hook.GetPlayerInfoForThisPlayerPed.Hook(
        GameAddress + 0x4D995D,
        [](CPlayerPed* self) { return &CWorld::Players()[self->GetID()]; }
    );

    hook.SetupPlayerPed.Activate();
    hook.Constructor.Activate();
    hook.ProcessControl.Activate();
    hook.GetPadFromPlayer.Activate();
    hook.GetPlayerInfoForThisPlayerPed.Activate();
}

void CPlayerPed::SetupPlayerPed(int playerID) {
    hook.SetupPlayerPed.GetTrampoline()(playerID);

    if (playerID != 0) {
        CWorld::Players()[playerID]
            .PlayerPed->PedType = PED_TYPE_PLAYER2;
    }
}

CPlayerPed* CPlayerPed::InitialiseInstance(CPlayerPed* self, int id, bool groupCreated) {
    hook.Constructor.GetTrampoline()(self, id, groupCreated);

    self->id = id;

    return self;
}

void CPlayerPed::ProcessControl() {
    if (id != 0)
        CPad::MapPad1To = id;

    hook.ProcessControl.GetTrampoline()(this);
}
