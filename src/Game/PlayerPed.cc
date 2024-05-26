// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/Hook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static struct {
    /// CPlayerPed::CPlayerPed()
    CHook<CPlayerPed* (LUNA_THISCALL *)(CPlayerPed*, int, bool)> Constructor;

    /// CPlayerPed::ProcessControl()
    CHook<void (LUNA_THISCALL *)(CPlayerPed*)> ProcessControl;

    /// CPlayerPed::GetPadFromPlayer()
    CHook<CPlayerInfo* (LUNA_THISCALL *)(CPlayerPed*)> GetPlayerInfoForThisPlayerPed;
} hook;

void CPlayerPed::InitialiseLuna() {
    hook.Constructor.Hook(
        GameAddress + 0x4D367D,
        [](CPlayerPed* self, int id, bool groupCreated) {
            hook.Constructor.Trampoline()(self, id, groupCreated);

            self->Initialise(id);

            return self;
        }
    );

    hook.ProcessControl.Hook(
        GameAddress + 0x4D47E9,
        [](CPlayerPed* self) { return self->ProcessControl(); }
    );

    hook.GetPlayerInfoForThisPlayerPed.Hook(
        GameAddress + 0x4D99CD,
        [](CPlayerPed* self) { return &CWorld::Players()[self->m_ID]; }
    );
}

CPlayerPed* CPlayerPed::Create(int id, bool groupCreated) {
    CPlayerPed* instance = reinterpret_cast<CPlayerPed*>(
        ::operator new(sizeof (CPlayerPed)));

    // Call the contructor.
    CallMethod<CPlayerPed*, int, bool>(
        GameAddress + 0x4D367D,
        instance, id, groupCreated
    );

    return instance;
}

void CPlayerPed::Destroy(CPlayerPed* instance) {
    CallMethod<void>(GameAddress + 0x4D3901, instance);

    ::operator delete(instance);
}

void CPlayerPed::Initialise(int id) {
    m_ID = id;

    if (id == 0)
        CPad::LocalPad = &m_Pad;
}

void CPlayerPed::ProcessControl() {
    CPad::CurrentPad = &m_Pad;
    hook.ProcessControl.Trampoline()(this);
}
