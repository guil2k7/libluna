// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Task.hh"
#include "../Common.hh"

namespace Luna::Game {
    class CTaskSimplePlayerOnFoot : public CTask {
    public:
        static inline CTaskSimplePlayerOnFoot* Create() {
            auto self = CTask::operator new(sizeof (CTaskSimplePlayerOnFoot));

            // Call the constructor.
            CallMethod<void*>(GameAddress + 0x547551, self);

            return reinterpret_cast<CTaskSimplePlayerOnFoot*>(self);
        }

    private:
        PADDING(0x34);
    };

    VALIDATE_SIZE(CTaskSimplePlayerOnFoot, 0x34);
}
