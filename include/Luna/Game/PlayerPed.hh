// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Ped.hh"
#include "Pad.hh"

namespace Luna::Game {

class CPlayerPed : public CPed {
public:
    static void InitializeLuna();

    static CPlayerPed* Create(int id, bool groupCreated);
    static void Destroy(CPlayerPed* instance);
    static void SetupPlayerPed(int id);

    void ProcessControl();

    inline int ID() const {
        return m_ID;
    }

    inline CPad* Pad() {
        return &m_Pad;
    }

    void _Initialize(int id);

private:
    PADDING(8);

    int m_ID;
    CPad m_Pad;
};

static_assert(sizeof (CPlayerPed) >= 1964 && sizeof (CPlayerPed) <= 1996);

} // namespce Luna::Game
