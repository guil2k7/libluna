// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/ThumbHook.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static struct {
    /// CPlayerPed::CPlayerPed()
    CThumbHook<CPlayerPed* (LUNA_THISCALL *)(CPlayerPed*, int, bool)> Constructor;

    /// CPlayerPed::SetupPlayerPed()
    CThumbHook<void (LUNA_STDCALL *)(int)> SetupPlayerPed;

    /// CPlayerPed::ProcessControl()
    CThumbHook<void (LUNA_THISCALL *)(CPlayerPed*)> ProcessControl;

    /// CPlayerPed::GetPadFromPlayer()
    CThumbHook<CPlayerInfo* (LUNA_THISCALL *)(CPlayerPed*)> GetPlayerInfoForThisPlayerPed;
} hook;

static LUNA_THISCALL CPlayerPed* HookImpl_Constructor(CPlayerPed* self, int id, bool groupCreated) {
    hook.Constructor.Trampoline()(self, id, groupCreated);

    self->_Initialize(id);

    return self;
}

static LUNA_THISCALL void HookImpl_ProcessControl(CPlayerPed* self) {
    return self->ProcessControl();
}

static LUNA_THISCALL CPlayerInfo* HookImpl_GetPlayerInfoForThisPlayerPed(CPlayerPed* self) {
    return &CWorld::Players()[self->ID()];
}

void CPlayerPed::SetupPlayerPed(int id) {
    hook.SetupPlayerPed.Trampoline()(id);

    if (id > 1)
        CWorld::Players()[id].PlayerPed->PedType = PED_TYPE_PLAYER_NETWORK;
}

void CPlayerPed::InitializeLuna() {
    hook.Constructor.Hook(GameAddress + 0x4D367D, HookImpl_Constructor);
    hook.ProcessControl.Hook(GameAddress + 0x4D47E9, HookImpl_ProcessControl);
    hook.GetPlayerInfoForThisPlayerPed.Hook(GameAddress + 0x4D99CD, HookImpl_GetPlayerInfoForThisPlayerPed);
    hook.SetupPlayerPed.Hook(GameAddress + 0x4D39A5, CPlayerPed::SetupPlayerPed);

    hook.Constructor.Activate();
    hook.ProcessControl.Activate();
    hook.GetPlayerInfoForThisPlayerPed.Activate();
    hook.SetupPlayerPed.Activate();
}

CPlayerPed* CPlayerPed::Create(int id, bool groupCreated) {
    CPlayerPed* instance = reinterpret_cast<CPlayerPed*>(
        ::operator new(sizeof (CPlayerPed)));

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

void CPlayerPed::_Initialize(int id) {
    m_ID = id;

    if (id == 0)
        CPad::LocalPad = &m_Pad;
}

void CPlayerPed::ProcessControl() {
    if (m_ID == 0)
        m_Pad.Clear();

    CPad::CurrentPad = &m_Pad;
    hook.ProcessControl.Trampoline()(this);
    CPad::CurrentPad = CPad::LocalPad;
}
