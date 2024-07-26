
// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../Packet.hh"
#include "../../Serde/Serde.hh"
#include "../../Game/Vector.hh"
#include "../../Game/Quaternion.hh"
#include <string>
#include <cstdint>

namespace Luna::Network::Code {

enum eServerQuitReason : uint8_t {
    SERVER_QUIT_REASON_TIMEOUT,
    SERVER_QUIT_REASON_QUIT,
    SERVER_QUIT_REASON_KICK_OR_BAN,
};

struct CStatsUpdate final : public Serde::ISerializable {
    LUNA_DEFINE_PACKET(false, 205)

    void Serialize(Serde::ISerializer& serializer) const;

    int32_t Money;
    int32_t DrunkLevel;
};

struct COnFootSync final : public Serde::ISerializable, Serde::IDeserializable {
    LUNA_DEFINE_PACKET(false, 207)

    void Serialize(Serde::ISerializer& serializer) const;
    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    int16_t LeftRight;
    int16_t UpDown;
    uint16_t Keys;

    union {
        uint8_t WeaponAdditionalKey;
        struct {
            uint8_t Weapon : 6;
            uint8_t AdditionalKey : 2;
        };
    };

    uint8_t SpecialAction;
    Game::CVector Position;
    Game::CQuaternion Rotation;
    float Health;
    float Armour;
    Game::CVector Velocity;
    uint16_t AnimationID;
    uint16_t AnimationFlags;
    uint16_t SurfingID;
    Game::CVector SurfingOffset;
};

struct CSetPlayerFacingAngle final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 19)

    void Deserialize(Serde::IDeserializer& deserializer);

    float Angle;
};

struct CServerJoin final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 137)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    uint32_t Color;
    uint8_t IsNPC;
    std::string PlayerName;

    // Additional Information: Keeping color parameter as 0 will make random color on each client.
};

struct CServerQuit final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 138)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    eServerQuitReason reason;
};

struct CSendSpawn final : public Serde::ISerializable {
    LUNA_DEFINE_PACKET(true, 52)

    void Serialize(Serde::ISerializer& serializer) const;
};

struct CRequestClass final : public Serde::ISerializable {
    LUNA_DEFINE_PACKET(true, 128)

    void Serialize(Serde::ISerializer& serializer) const;

    uint16_t ID;
};

struct CRequestSpawn final : public Serde::ISerializable {
    LUNA_DEFINE_PACKET(true, 129)

    void Serialize(Serde::ISerializer& serializer) const;
};

struct CInitGame final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 139)

    void Deserialize(Serde::IDeserializer& deserializer);

    bool ZoneNames;
    bool UseCJWalk;
    bool AllowWeapons;
    bool LimitGlobalChatRadius;
    float GlobalChatRadius;
    bool StuntBonus;
    float NameTagDistance;
    bool DisableEnterExits;
    bool NameTagLOS;
    bool ManualVehEngineAndLights;
    uint32_t SpawnsAvailable;
    uint16_t PlayerID;
    bool ShowNameTags;
    uint32_t ShowPlayerMarkers;
    uint8_t WorldTime;
    uint8_t Weather;
    float Gravity;
    bool LanMode;
    uint32_t DeathDropMoney;
    bool Instagib;
    uint32_t OnfootRate;
    uint32_t InCarRate;
    uint32_t WeaponRate;
    uint32_t Multiplier;
    uint32_t LagCompMode;
    std::string HostName;
    // uint8_t VehicleModels;
    uint32_t VehicleFriendlyFire;

    // Additional Information: vehicleModels is an array of used vehicle models with size 212.
};

struct CUpdateScoresAndPings final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 155)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    int32_t Score;
    uint32_t Ping;
};

struct CClientCheck final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 103)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t Type;
    uint32_t Address;
    uint16_t Offset;
    uint16_t Count;
};

struct CGameModeRestart final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 40)

    void Deserialize(Serde::IDeserializer& deserializer);

    // Additional Information: This RPC reconnects a player to the server showing him "The server is restarting..." message.
};

struct CApplyPlayerAnimation final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 86)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    std::string AnimLib;
    std::string AnimName;
    float Delta;
    bool Loop;
    bool Lockx;
    bool Locky;
    bool Freeze;
    uint32_t Time;
};

struct CClearPlayerAnimation final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 87)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
};

struct CDeathBroadcast final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 166)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
};

struct CSetPlayerName final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 11)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    std::string Name;
    uint8_t Success;

    // Additional Information: Keep success parameter as 1.
};

struct CSetPlayerPos final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 12)

    void Deserialize(Serde::IDeserializer& deserializer);

    Game::CVector Position;
};

struct CSetPlayerPosFindZ final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 13)

    void Deserialize(Serde::IDeserializer& deserializer);

    float X;
    float Y;
    float Z;
};

struct CSetPlayerSkillLevel final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 34)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    uint32_t SkillID;
    uint16_t Level;
};

struct CSetPlayerSkin final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 153)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint32_t PlayerID;
    uint32_t SkinID;
};

struct CSetPlayerTime final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 29)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t Hour;
    uint8_t Minute;
};

struct CSetPlayerSpecialAction final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 88)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t ActionID;
};

struct CSetWeather final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 152)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t WeatherID;
};

struct CSetWorldBounds final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 17)

    void Deserialize(Serde::IDeserializer& deserializer);

    float MaxX;
    float MinX;
    float MaxY;
    float MinY;
};

struct CSetPlayerVelocity final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 90)

    void Deserialize(Serde::IDeserializer& deserializer);

    float X;
    float Y;
    float Z;
};

struct CTogglePlayerControllable final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 15)

    void Deserialize(Serde::IDeserializer& deserializer);

    bool Moveable;
};

struct CTogglePlayerSpectating final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 124)

    void Deserialize(Serde::IDeserializer& deserializer);

    bool Spectating;
};

struct CToggleClock final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 30)

    void Deserialize(Serde::IDeserializer& deserializer);

    bool Toggle;
};

struct CSetPlayerTeam final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 69)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    uint8_t TeamID;
};

struct CPlaySound final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 16)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint32_t SoundID;
    float X;
    float Y;
    float Z;
};

struct CGivePlayerMoney final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 18)

    void Deserialize(Serde::IDeserializer& deserializer);

    int32_t Money;
};

struct CResetPlayerMoney final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 20)

    void Deserialize(Serde::IDeserializer& deserializer);
};

struct CResetPlayerWeapons final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 21)

    void Deserialize(Serde::IDeserializer& deserializer);
};

struct CGivePlayerWeapon final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 22)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint32_t WeaponID;
    uint32_t Bullets;
};

struct CPlayAudioStream final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 41)

    void Deserialize(Serde::IDeserializer& deserializer);

    std::string Url;
    float X;
    float Y;
    float Z;
    float Radius;
    bool UsePos;
};

struct CPlayCrimeReport final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 112)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t SuspectID;
    uint32_t InVehicle;
    uint32_t VehicleModel;
    uint32_t VehicleColor;
    uint32_t Crime;
    float X;
    float Y;
    float Z;
};

struct CStopAudioStream final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 42)

    void Deserialize(Serde::IDeserializer& deserializer);
};

struct CRemoveBuilding final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 43)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint32_t ObjectModel;
    float X;
    float Y;
    float Z;
    float Radius;
};

struct CSetPlayerHealth final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 14)

    void Deserialize(Serde::IDeserializer& deserializer);

    float Health;
};

struct CSetPlayerArmour final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 66)

    void Deserialize(Serde::IDeserializer& deserializer);

    float Armour;
};

struct CSetWeaponAmmo final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 145)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t WeaponID;
    uint16_t Ammo;
};

struct CSetCameraBehind final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 162)

    void Deserialize(Serde::IDeserializer& deserializer);
};

struct CSetArmedWeapon final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 67)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint32_t WeaponID;
};

struct CWorldPlayerAdd final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 32)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    uint8_t Team;
    uint32_t SkinId;
    float PosX;
    float PosY;
    float PosZ;
    float FacingAngle;
    uint32_t PlayerColor;
    uint8_t FightingStyle;
    uint16_t SkillLevel[11];
};

struct CWorldPlayerRemove final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 163)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
};

struct CInterpolateCamera final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 82)

    void Deserialize(Serde::IDeserializer& deserializer);

    bool PosSet;
    float FromPosX;
    float FromPosY;
    float FromPosZ;
    float ToPosX;
    float ToPosY;
    float ToPosZ;
    uint32_t Time;
    uint8_t CutType;
};

struct CCreateExplosion final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 79)

    void Deserialize(Serde::IDeserializer& deserializer);

    float X;
    float Y;
    float Z;
    uint32_t Type;
    float Radius;
};

struct CSendDeathMessage final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 55)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t KillerID;
    uint16_t PlayerID;
    uint8_t Reason;
};

struct CSendGameTimeUpdate final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 60)

    void Deserialize(Serde::IDeserializer& deserializer);

    int32_t Time;
};

struct CSendClientMessage final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 93)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint32_t Color;
    std::string Message;
};

struct CSetShopName final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 33)

    void Deserialize(Serde::IDeserializer& deserializer);

    std::string Name;
};

struct CSetPlayerDrunkLevel final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 35)

    void Deserialize(Serde::IDeserializer& deserializer);

    int32_t DrunkLevel;
};

struct CSetPlayerFightingStyle final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 89)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    uint8_t FightStyle;
};

struct CSetInterior final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 156)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t InteriorID;
};

struct CSetPlayerColor final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 72)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint16_t PlayerID;
    uint32_t Color;
};

struct CForceClassSelection final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 74)

    void Deserialize(Serde::IDeserializer& deserializer);
};

struct CToggleWidescreen final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 111)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t Enable;
};

struct CSetPlayerWantedLevel final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 133)

    void Deserialize(Serde::IDeserializer& deserializer);

    uint8_t WantedLevel;
};

struct CSetCameraPos final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 157)

    void Deserialize(Serde::IDeserializer& deserializer);

    float LookPosX;
    float LookPosY;
    float LookPosZ;
};

struct CSetCameraLookAt final : public Serde::IDeserializable {
    LUNA_DEFINE_PACKET(true, 158)

    void Deserialize(Serde::IDeserializer& deserializer);

    float LookPosX;
    float LookPosY;
    float LookPosZ;
    uint8_t CutType;
};

} // namespace Luna::Network::Code

#include "Player.inl"
