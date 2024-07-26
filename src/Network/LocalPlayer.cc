// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Network/LocalPlayer.hh>
#include <Luna/Network/Code/Player.hh>
#include <Luna/Serde/BitSerde.hh>
#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/World.hh>
#include <Luna/Game/Task/TaskSimplePlayerOnFoot.hh>

using namespace Luna;
using namespace Luna::Network;
using namespace Luna::Game;

void CLocalPlayerComponent::Install(CClient& client) {
    #define REGISTER_HANDLER_FOR_RPC(id, method)                                   \
    client.RegisterHandlerForRPC(id, CRpcEventHandler(                             \
        reinterpret_cast<void*>(this),                                             \
        [](void* userData, CClient& client, uint8_t const* data, size_t bitSize) { \
            ((CLocalPlayerComponent*)userData)->method(client, data, bitSize);    \
        }                                                                          \
    ))

    REGISTER_HANDLER_FOR_RPC(Code::CSetPlayerPos::PACKET_ID, ProcessSetPlayerPos);

    #undef REGISTER_HANDLER_FOR_RPC
}

void CLocalPlayerComponent::ProcessSetPlayerPos(CClient& client, uint8_t const* rawData, size_t bitSize) {
    Code::CSetPlayerPos data;

    Serde::CBitDeserializer deserializer(rawData, bitSize);
    deserializer.DeserializeObject(data);

    CWorld::Players()[0].PlayerPed->Matrix().Position = data.Position;
}
