// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

#include <Luna/Network/RemotePlayer.hh>
#include <Luna/Network/Code/Player.hh>
#include <Luna/Serde/BitSerde.hh>
#include <Luna/Game/PlayerPed.hh>
#include <Luna/Game/Pad.hh>
#include <Luna/Game/World.hh>
#include <Luna/Game/Task/TaskSimplePlayerOnFoot.hh>

using namespace Luna;
using namespace Luna::Network;
using namespace Luna::Game;

void CRemotePlayerComponent::Install(CClient& client) {
    #define REGISTER_HANDLER_FOR_RPC(id, method)                                   \
    client.RegisterHandlerForRPC(id, CRpcEventHandler(                             \
        reinterpret_cast<void*>(this),                                             \
        [](void* userData, CClient& client, uint8_t const* data, size_t bitSize) { \
            ((CRemotePlayerComponent*)userData)->method(client, data, bitSize);    \
        }                                                                          \
    ))

    REGISTER_HANDLER_FOR_RPC(Code::CServerJoin::PACKET_ID, ProcessServerJoin);

    #undef REGISTER_HANDLER_FOR_RPC

    client.RegisterPacketHandler(this);
}

bool CRemotePlayerComponent::OnReceivePacket(CClient& client, PacketID id, uint8_t const* data, size_t bitSize) {
    switch (id) {
    case Code::COnFootSync::PACKET_ID:
        ProcessOnFootSync(client, data, bitSize);
        break;

    default:
        return false;
    }

    return true;
}

void CRemotePlayerComponent::ProcessServerJoin(CClient& client, uint8_t const* rawData, size_t bitSize) {
    Code::CServerJoin data;

    Serde::CBitDeserializer deserializer(rawData, bitSize);
    deserializer.DeserializeObject(data);

    CPlayerPed::SetupPlayerPed(data.PlayerID + 2);

    CPlayerPed* mainPlayer = CWorld::Players()[0].PlayerPed;
    CPlayerPed* remotePlayer = CWorld::Players()[data.PlayerID + 2].PlayerPed;

    remotePlayer->TaskManager()->SetTask(
        CTaskSimplePlayerOnFoot::Create(), 4, false);

    remotePlayer->Matrix() = mainPlayer->Matrix();

    Code::CRequestClass requestClass;
    requestClass.ID = 0;

    client.Send(requestClass, RakNet::HIGH_PRIORITY, RakNet::RELIABLE_ORDERED);
    client.Send(Code::CRequestSpawn(), RakNet::HIGH_PRIORITY, RakNet::RELIABLE_ORDERED);
    client.Send(Code::CSendSpawn(), RakNet::HIGH_PRIORITY, RakNet::RELIABLE_ORDERED);
}

void CRemotePlayerComponent::ProcessOnFootSync(CClient& client, uint8_t const* rawData, size_t bitSize) {
    Code::COnFootSync data;

    Serde::CBitDeserializer deserializer(rawData, bitSize);
    deserializer.DeserializeObject(data);

    CPlayerPed* player = CWorld::Players()[data.PlayerID + 2].PlayerPed;
    CPad* pad = player->Pad();

    pad->LeftRight = data.LeftRight;
    pad->UpDown = data.UpDown;
    pad->Keys = data.Keys;
}
