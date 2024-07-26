// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Task.hh"
#include "../Common.hh"

namespace Luna::Game {

class CTaskSimplePlayerOnFoot : public CTask {
public:
    static CTaskSimplePlayerOnFoot* Create();

private:
    PADDING(0x34);
};

VALIDATE_SIZE(CTaskSimplePlayerOnFoot, 0x34);

inline CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Create() {
    auto self = CTask::operator new(sizeof (CTaskSimplePlayerOnFoot));

    // Constructor.
    CallMethod<void*>(GameAddress + 0x547551, self);

    return reinterpret_cast<CTaskSimplePlayerOnFoot*>(self);
}

} // namespace Luna::Game
