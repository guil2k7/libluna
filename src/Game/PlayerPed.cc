// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/MemoryExec.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static struct {
    /// CPlayerPed::CPlayerPed()
    CFunction<CPlayerPed* (LUNA_THISCALL *)(CPlayerPed*, int, bool)> Constructor;

    /// CPlayerPed::ProcessControl()
    CFunction<void (LUNA_THISCALL *)(CPlayerPed*)> ProcessControl;

    /// CPlayerPed::GetPadFromPlayer()
    CFunction<CPlayerInfo* (LUNA_THISCALL *)(CPlayerPed*)> GetPlayerInfoForThisPlayerPed;
} trampoline;

static LUNA_THISCALL CPlayerPed* hook_Constructor(CPlayerPed* self, int id, bool groupCreated) {
    trampoline.Constructor(self, id, groupCreated);

    self->_Initialise(id);

    return self;
}

static LUNA_THISCALL void hook_ProcessControl(CPlayerPed* self) {
    return self->ProcessControl();
}

static LUNA_THISCALL CPlayerInfo* hook_GetPlayerInfoForThisPlayerPed(CPlayerPed* self) {
    return &CWorld::Players()[self->ID()];
}

void CPlayerPed::InitialiseLuna() {
    MakeHook(&trampoline.Constructor, GameAddress + 0x4D367D, hook_Constructor);
    MakeHook(&trampoline.ProcessControl, GameAddress + 0x4D47E9, hook_ProcessControl);
    MakeHook(&trampoline.GetPlayerInfoForThisPlayerPed, GameAddress + 0x4D99CD, hook_GetPlayerInfoForThisPlayerPed);
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

void CPlayerPed::_Initialise(int id) {
    m_ID = id;

    if (id == 0)
        CPad::LocalPad = &m_Pad;
}

void CPlayerPed::ProcessControl() {
    if (m_ID == 0)
        m_Pad.Clear();

    CPad::CurrentPad = &m_Pad;
    trampoline.ProcessControl(this);
}
