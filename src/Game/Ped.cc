// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Game/Ped.hh>
#include <Luna/Game/Task/CTaskComplexDie.hh>
#include <algorithm>

using namespace Luna;
using namespace Luna::Game;

void CPed::SetHealth(float value) {
    m_Health = std::min(value, m_Health);

    if (value == 0.0f) {
        TaskManager()->SetTask(
            CTaskComplexDie::Create(), 4, false);
    }
}
