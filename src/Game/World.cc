// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Game/World.hh>
#include <Luna/Game/Common.hh>

using namespace Luna;
using namespace Luna::Game;

void CWorld::InitializeLuna() {
    *reinterpret_cast<CPlayerInfo**>(GameAddress + 0x6883C0)
        = reinterpret_cast<CPlayerInfo*>(::operator new(sizeof (CPlayerInfo) * 1024));
}
