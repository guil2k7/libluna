// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Ped.hh"

namespace Luna::Game {
    class CPlayerPed : public CPed {
    public:
        /* <NOTSA> */

        static LUNA_THISCALL CPlayerPed* InitialiseInstance(
            CPlayerPed* self, int id, bool groupCreated);

        static inline void ReleaseInstance(CPlayerPed* self) {
            CallMethod<void>(GameAddress + 0x4D3891, self);
        }

        static inline CPlayerPed* Create(int id, bool groupCreated) {
            CPlayerPed* instance = reinterpret_cast<CPlayerPed*>(
                ::operator new(sizeof (CPlayerPed)));

            return InitialiseInstance(instance, id, groupCreated);
        }

        static inline void Destroy(CPlayerPed* self) {
            ReleaseInstance(self);
            ::operator delete(self);
        }

        /* </NOTSA> */

        static void SetupPlayerPed(int playerID);

        CPlayerPed() = delete;
        ~CPlayerPed() = delete;

        void ProcessControl();

        inline int GetID() const {
            return id;
        }

    private:
        PADDING(8);

        /* <NOTSA> */
        int id;
        /* </NOTSA> */
    };

    static_assert(sizeof (CPlayerPed) >= 1964 && sizeof (CPlayerPed) <= 1996);

    class CPlayerPedMod {
    public:
        static void Install();
    };
}
