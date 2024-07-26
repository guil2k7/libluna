// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/World.hh>
#include <Luna/Core/Hooker.hh>

using namespace Luna;
using namespace Luna::Core;
using namespace Luna::Game;

static struct {
    /// CPlayerPed::CPlayerPed()
    CPlayerPed* (LUNA_THISCALL *Constructor)(CPlayerPed*, int, bool);

    /// CPlayerPed::SetupPlayerPed()
    void (LUNA_STDCALL *SetupPlayerPed)(int);

    /// CPlayerPed::ProcessControl()
    void (LUNA_THISCALL *ProcessControl)(CPlayerPed*);

    /// CPlayerPed::GetPadFromPlayer()
    CPlayerInfo* (LUNA_THISCALL *GetPlayerInfoForThisPlayerPed)(CPlayerPed*);
} trampoline;

static LUNA_THISCALL CPlayerPed* HookImpl_Constructor(CPlayerPed* self, int id, bool groupCreated) {
    trampoline.Constructor(self, id, groupCreated);

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
    trampoline.SetupPlayerPed(id);

    if (id > 1)
        CWorld::Players()[id].PlayerPed->PedType = PED_TYPE_PLAYER_NETWORK;
}

void CPlayerPed::InitializeLuna() {
    trampoline.Constructor = CHooker(GameAddress + 0x4D367D, HookImpl_Constructor, true).Hook();
    trampoline.ProcessControl = CHooker(GameAddress + 0x4D47E9, HookImpl_ProcessControl, true).Hook();
    trampoline.GetPlayerInfoForThisPlayerPed = CHooker(GameAddress + 0x4D99CD, HookImpl_GetPlayerInfoForThisPlayerPed, true).Hook();
    trampoline.SetupPlayerPed = CHooker(GameAddress + 0x4D39A5, CPlayerPed::SetupPlayerPed, true).Hook();
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
    trampoline.ProcessControl(this);
    CPad::CurrentPad = CPad::LocalPad;
}
