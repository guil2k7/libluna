// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../Packet.hh"
#include "../../Serde/Serde.hh"
#include "../../Game/Vector.hh"
#include <cstdint>
#include <string>

namespace Luna::Network::Code {
    enum eServerQuitReason : uint8_t {
        SERVER_QUIT_REASON_TIMEOUT,
        SERVER_QUIT_REASON_QUIT,
        SERVER_QUIT_REASON_KICK_OR_BAN,
    };

    // struct CAimSync final : public Serde::ISerializable {
    //     LUNA_DEFINE_PACKET(false, 20)

    //     void Serialize(Serde::ISerializer& serializer) const {
    //         serializer.SerializeU8(CamMode);
    //         serializer.SerializeObject(CamFront);
    //         serializer.SerializeObject(CamPos);
    //         serializer.SerializeF32(AimZ);
    //         serializer.SerializeU8(WeaponState << 6 | CamZoom);
    //         serializer.SerializeU8(AspectRatio);
    //     }

    //     uint8_t CamMode;
    //     Game::CVector CamFront;
    //     Game::CVector CamPos;
    //     float AimZ;
    //     uint8_t WeaponState : 2;
    //     uint8_t CamZoom : 6;
    //     uint8_t AspectRatio;
    // };

    // TODO:
    // struct CWeaponsUpdate final : public Serde::ISerializable {
    //     LUNA_DEFINE_PACKET(false, 204)

    //     uint8_t Slot0, Weapon0;   uint16_t Ammo0;
    //     uint8_t Slot1, Weapon1;   uint16_t Ammo1;
    //     uint8_t Slot2, Weapon2;   uint16_t Ammo2;
    //     uint8_t Slot3, Weapon3;   uint16_t Ammo3;
    //     uint8_t Slot4, Weapon4;   uint16_t Ammo4;
    //     uint8_t Slot5, Weapon5;   uint16_t Ammo5;
    //     uint8_t Slot6, Weapon6;   uint16_t Ammo6;
    //     uint8_t Slot7, Weapon7;   uint16_t Ammo7;
    //     uint8_t Slot8, Weapon8;   uint16_t Ammo8;
    //     uint8_t Slot9, Weapon9;   uint16_t Ammo9;
    //     uint8_t Slot10, Weapon10; uint16_t Ammo10;
    //     uint8_t Slot11, Weapon11; uint16_t Ammo11;
    // };

    struct CStatsUpdate final : public Serde::ISerializable {
        LUNA_DEFINE_PACKET(false, 205)

        void Serialize(Serde::ISerializer& serializer) const {
            serializer.SerializeI32(Money);
            serializer.SerializeI32(DrunkLevel);
        }

        int32_t Money;
        int32_t DrunkLevel;
    };

    // struct CBulletSync final : public Serde::ISerializable {
    //     LUNA_DEFINE_PACKET(false, 206)

    //     void Serialize(Serde::ISerializer& serializer) const {
    //         serializer.SerializeU8(HitType);
    //         serializer.SerializeU16(HitID);
    //         serializer.SerializeObject(Origin);
    //         serializer.SerializeObject(HitPos);
    //         serializer.SerializeObject(Offset);
    //         serializer.SerializeF32(WeaponID);
    //     }

    //     uint8_t HitType;
    //     uint16_t HitID;
    //     Game::CVector Origin;
    //     Game::CVector HitPos;
    //     Game::CVector Offset;
    //     uint8_t WeaponID;
    // };

    struct COnFootSync final : public Serde::ISerializable, Serde::IDeserializable {
        LUNA_DEFINE_PACKET(false, 207)

        void Serialize(Serde::ISerializer& serializer) const {
            serializer.SerializeU16(LeftRight);
            serializer.SerializeU16(UpDown);
            serializer.SerializeU16(Keys);
            serializer.SerializeObject(Position);
            serializer.SerializeObject(Rotation);
            serializer.SerializeU8(Health);
            serializer.SerializeU8(Armour);
            serializer.SerializeU8(WeaponAdditionalKey);
            serializer.SerializeU8(SpecialAction);
            serializer.SerializeObject(Velocity);
            serializer.SerializeObject(SurfingOffset);
            serializer.SerializeU16(SurfingID);
            serializer.SerializeU16(AnimationID);
            serializer.SerializeU16(AnimationFlags);
        }

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();

            if (deserializer.DeserializeBool())
                LeftRight = deserializer.DeserializeI16();

            if (deserializer.DeserializeBool())
                UpDown = deserializer.DeserializeI16();

            Keys = deserializer.DeserializeU16();

            deserializer.DeserializeObject(Position);

            deserializer.DeserializeNormQuat(
                Rotation.w,
                Rotation.x,
                Rotation.y,
                Rotation.z
            );

            uint8_t health, armour;
            uint8_t healthArmour = deserializer.DeserializeU8();

            health = (health >> 4) & 0xF;
            armour = armour & 0xF;

            if (health == 0xF)
                Health = 100.0F;
            else if (health == 0)
                Health = 0.0F;
            else
                Health = health * 7.0F;

            if (armour == 0xF)
                Armour = 100.0F;
            else if (armour == 0)
                Armour = 0.0F;
            else
                Armour = armour * 7.0F;

            WeaponAdditionalKey = deserializer.DeserializeU8();
            SpecialAction = deserializer.DeserializeU8();

            deserializer.DeserializeCompressedVec(
                Velocity.x,
                Velocity.y,
                Velocity.z
            );

            if (deserializer.DeserializeBool()) {
                SurfingID = deserializer.DeserializeU16();
                deserializer.DeserializeObject(SurfingOffset);
            }
            else {
                SurfingID = 0xFFFF;
            }
        }

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
        Game::CVector4D Rotation;
        float Health;
        float Armour;
        Game::CVector Velocity;
        uint16_t AnimationID;
        uint16_t AnimationFlags;
        uint16_t SurfingID;
        Game::CVector SurfingOffset;
    };

    // TODO: Move to vehicle component.
    // struct CUnoccupiedSync final : public Serde::ISerializable {
    //     LUNA_DEFINE_PACKET(false, 209)

    //     uint16_t VehicleID;
    //     uint8_t SeatID;
    //     Game::CVector Roll;
    //     Game::CVector Direction;
    //     Game::CVector Pos;
    //     Game::CVector AngularVelocity;
    //     float VehicleHealth;
    // };

    // TODO: Move to vehicle component.
    // struct CTrailerSync final : public Serde::ISerializable {
    //     LUNA_DEFINE_PACKET(false, 210)

    //     uint16_t TrailerID;
    //     Game::CVector Pos;
    //     Game::CVector4D quat;
    //     Game::CVector Velocity;
    //     Game::CVector AngularVelocity;
    // };

    // struct CPassengerSync final : public Serde::ISerializable {
    //     LUNA_DEFINE_PACKET(false, 211)

    //     uint16_t VehicleID;
    //     uint8_t DriveBy : 2;
    //     uint8_t SeatId : 6;
    //     uint8_t AdditionalKey : 2;
    //     uint8_t WeaponId : 6;
    //     uint8_t Health;
    //     uint8_t Armour;
    //     uint16_t Lrkey;
    //     uint16_t Udkey;
    //     uint16_t Keys;
    //     Game::CVector Pos;
    // };

    // struct CSpectatingSync final : public Serde::ISerializable {
    //     LUNA_DEFINE_PACKET(false, 212)

    //     void Serialize(Serde::ISerializer& serializer) const {
    //         serializer.SerializeU16(LrKey);
    //         serializer.SerializeU16(UdKey);
    //         serializer.SerializeU16(Keys);
    //         serializer.SerializeObject(Pos);
    //     }

    //     uint16_t LrKey;
    //     uint16_t UdKey;
    //     uint16_t Keys;
    //     Game::CVector Pos;
    // };

    struct CSetPlayerFacingAngle final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 19)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Angle = deserializer.DeserializeF32();
        }

        float Angle;
    };

    struct CServerJoin final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 137)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            Color = deserializer.DeserializeU32();
            IsNPC = deserializer.DeserializeU8();

            uint8_t playerNameLength = deserializer.DeserializeU8();
            PlayerName.resize(playerNameLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(PlayerName.data()), playerNameLength);
        }

        uint16_t PlayerID;
        uint32_t Color;
        uint8_t IsNPC;
        std::string PlayerName;

        // Additional Information: Keeping color parameter as 0 will make random color on each client.
    };

    struct CServerQuit final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 138)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            reason = static_cast<eServerQuitReason>(deserializer.DeserializeU8());
        }

        uint16_t PlayerID;
        eServerQuitReason reason;
    };

    struct CSendSpawn final : public Serde::ISerializable {
        LUNA_DEFINE_PACKET(true, 52)

        void Serialize(Serde::ISerializer& serializer) const {}
    };

    struct CRequestSpawn final : public Serde::ISerializable {
        LUNA_DEFINE_PACKET(true, 129)

        void Serialize(Serde::ISerializer& serializer) const {}
    };

    struct CInitGame final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 139)

        void Deserialize(Serde::IDeserializer& deserializer) {
            ZoneNames = deserializer.DeserializeBool();
            UseCJWalk = deserializer.DeserializeBool();
            AllowWeapons = deserializer.DeserializeBool();
            LimitGlobalChatRadius = deserializer.DeserializeBool();
            GlobalChatRadius = deserializer.DeserializeF32();
            StuntBonus = deserializer.DeserializeBool();
            NameTagDistance = deserializer.DeserializeF32();
            DisableEnterExits = deserializer.DeserializeBool();
            NameTagLOS = deserializer.DeserializeBool();
            ManualVehEngineAndLights = deserializer.DeserializeBool();
            SpawnsAvailable = deserializer.DeserializeU32();
            PlayerID = deserializer.DeserializeU16();
            ShowNameTags = deserializer.DeserializeBool();
            ShowPlayerMarkers = deserializer.DeserializeU32();
            WorldTime = deserializer.DeserializeU8();
            Weather = deserializer.DeserializeU8();
            Gravity = deserializer.DeserializeF32();
            LanMode = deserializer.DeserializeBool();
            DeathDropMoney = deserializer.DeserializeU32();
            Instagib = deserializer.DeserializeBool();
            OnfootRate = deserializer.DeserializeU32();
            InCarRate = deserializer.DeserializeU32();
            WeaponRate = deserializer.DeserializeU32();
            Multiplier = deserializer.DeserializeU32();
            LagCompMode = deserializer.DeserializeU32();

            uint8_t hostNameLength = deserializer.DeserializeU8();

            HostName.resize(hostNameLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(HostName.data()), hostNameLength);

            deserializer.SkipBytes(212); // vehicleModels
            VehicleFriendlyFire = deserializer.DeserializeU32();
        }

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

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            Score = deserializer.DeserializeI32();
            Ping = deserializer.DeserializeU32();
        }

        uint16_t PlayerID;
        int32_t Score;
        uint32_t Ping;
    };

    struct CClientCheck final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 103)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Type = deserializer.DeserializeU8();
            Address = deserializer.DeserializeU32();
            Offset = deserializer.DeserializeU16();
            Count = deserializer.DeserializeU16();
        }

        uint8_t Type;
        uint32_t Address;
        uint16_t Offset;
        uint16_t Count;
    };

    struct CGameModeRestart final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 40)

        void Deserialize(Serde::IDeserializer& deserializer) {}

        // Additional Information: This RPC reconnects a player to the server showing him "The server is restarting..." message.
    };

    struct CApplyPlayerAnimation final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 86)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();

            uint8_t animLibLength = deserializer.DeserializeU8();
            AnimLib.resize(animLibLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(AnimLib.data()), animLibLength);

            uint8_t animNameLength = deserializer.DeserializeU8();
            AnimName.resize(animNameLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(AnimName.data()), animNameLength);

            Delta = deserializer.DeserializeF32();
            Loop = deserializer.DeserializeBool();
            Lockx = deserializer.DeserializeBool();
            Locky = deserializer.DeserializeBool();
            Freeze = deserializer.DeserializeBool();
            Time = deserializer.DeserializeU32();
        }

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

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
    };

    struct CDeathBroadcast final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 166)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
    };

    struct CSetPlayerName final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 11)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            uint8_t nameLength = deserializer.DeserializeU8();

            Name.resize(nameLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Name.data()), nameLength);

            Success = deserializer.DeserializeU8();
        }

        uint16_t PlayerID;
        std::string Name;
        uint8_t Success;

        // Additional Information: Keep success parameter as 1.
    };

    struct CSetPlayerPos final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 12)

        void Deserialize(Serde::IDeserializer& deserializer) {
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

        float X;
        float Y;
        float Z;
    };

    struct CSetPlayerPosFindZ final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 13)

        void Deserialize(Serde::IDeserializer& deserializer) {
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

        float X;
        float Y;
        float Z;
    };

    struct CSetPlayerSkillLevel final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 34)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            SkillID = deserializer.DeserializeU32();
            Level = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
        uint32_t SkillID;
        uint16_t Level;
    };

    struct CSetPlayerSkin final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 153)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU32();
            SkinID = deserializer.DeserializeU32();
        }

        uint32_t PlayerID;
        uint32_t SkinID;
    };

    struct CSetPlayerTime final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 29)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Hour = deserializer.DeserializeU8();
            Minute = deserializer.DeserializeU8();
        }

        uint8_t Hour;
        uint8_t Minute;
    };

    struct CSetPlayerSpecialAction final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 88)

        void Deserialize(Serde::IDeserializer& deserializer) {
            ActionID = deserializer.DeserializeU8();
        }

        uint8_t ActionID;
    };

    struct CSetWeather final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 152)

        void Deserialize(Serde::IDeserializer& deserializer) {
            WeatherID = deserializer.DeserializeU8();
        }

        uint8_t WeatherID;
    };

    struct CSetWorldBounds final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 17)

        void Deserialize(Serde::IDeserializer& deserializer) {
            MaxX = deserializer.DeserializeF32();
            MinX = deserializer.DeserializeF32();
            MaxY = deserializer.DeserializeF32();
            MinY = deserializer.DeserializeF32();
        }

        float MaxX;
        float MinX;
        float MaxY;
        float MinY;
    };

    struct CSetPlayerVelocity final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 90)

        void Deserialize(Serde::IDeserializer& deserializer) {
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

        float X;
        float Y;
        float Z;
    };

    struct CTogglePlayerControllable final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 15)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Moveable = deserializer.DeserializeU8();
        }

        bool Moveable;
    };

    struct CTogglePlayerSpectating final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 124)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Spectating = deserializer.DeserializeU32();
        }

        bool Spectating;
    };

    struct CToggleClock final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 30)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Toggle = deserializer.DeserializeU8();
        }

        bool Toggle;
    };

    struct CSetPlayerTeam final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 69)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            TeamID = deserializer.DeserializeU8();
        }

        uint16_t PlayerID;
        uint8_t TeamID;
    };

    struct CPlaySound final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 16)

        void Deserialize(Serde::IDeserializer& deserializer) {
            SoundID = deserializer.DeserializeU32();
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

        uint32_t SoundID;
        float X;
        float Y;
        float Z;
    };

    struct CGivePlayerMoney final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 18)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Money = deserializer.DeserializeI32();
        }

        int32_t Money;
    };

    struct CResetPlayerMoney final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 20)

        void Deserialize(Serde::IDeserializer& deserializer) {}
    };

    struct CResetPlayerWeapons final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 21)

        void Deserialize(Serde::IDeserializer& deserializer) {}
    };

    struct CGivePlayerWeapon final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 22)

        void Deserialize(Serde::IDeserializer& deserializer) {
            WeaponID = deserializer.DeserializeU32();
            Bullets = deserializer.DeserializeU32();
        }

        uint32_t WeaponID;
        uint32_t Bullets;
    };

    struct CPlayAudioStream final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 41)

        void Deserialize(Serde::IDeserializer& deserializer) {
            uint8_t urlLength = deserializer.DeserializeU8();

            Url.resize(urlLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Url.data()), urlLength);
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
            Radius = deserializer.DeserializeF32();
            UsePos = deserializer.DeserializeU8();
        }

        std::string Url;
        float X;
        float Y;
        float Z;
        float Radius;
        bool UsePos;
    };

    struct CPlayCrimeReport final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 112)

        void Deserialize(Serde::IDeserializer& deserializer) {
            SuspectID = deserializer.DeserializeU16();
            InVehicle = deserializer.DeserializeU32();
            VehicleModel = deserializer.DeserializeU32();
            VehicleColor = deserializer.DeserializeU32();
            Crime = deserializer.DeserializeU32();
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

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

        void Deserialize(Serde::IDeserializer& deserializer) {}
    };

    struct CRemoveBuilding final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 43)

        void Deserialize(Serde::IDeserializer& deserializer) {
            ObjectModel = deserializer.DeserializeU32();
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
            Radius = deserializer.DeserializeF32();
        }

        uint32_t ObjectModel;
        float X;
        float Y;
        float Z;
        float Radius;
    };

    struct CSetPlayerHealth final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 14)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Health = deserializer.DeserializeF32();
        }

        float Health;
    };

    struct CSetPlayerArmour final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 66)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Armour = deserializer.DeserializeF32();
        }

        float Armour;
    };

    struct CSetWeaponAmmo final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 145)

        void Deserialize(Serde::IDeserializer& deserializer) {
            WeaponID = deserializer.DeserializeU8();
            Ammo = deserializer.DeserializeU16();
        }

        uint8_t WeaponID;
        uint16_t Ammo;
    };

    struct CSetCameraBehind final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 162)

        void Deserialize(Serde::IDeserializer& deserializer) {}
    };

    struct CSetArmedWeapon final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 67)

        void Deserialize(Serde::IDeserializer& deserializer) {
            WeaponID = deserializer.DeserializeU32();
        }

        uint32_t WeaponID;
    };

    struct CWorldPlayerAdd final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 32)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            Team = deserializer.DeserializeU8();
            SkinId = deserializer.DeserializeU32();
            PosX = deserializer.DeserializeF32();
            PosY = deserializer.DeserializeF32();
            PosZ = deserializer.DeserializeF32();
            FacingAngle = deserializer.DeserializeF32();
            PlayerColor = deserializer.DeserializeU32();
            FightingStyle = deserializer.DeserializeU8();
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(SkillLevel), 22);
        }

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

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
    };

    struct CInterpolateCamera final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 82)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PosSet = deserializer.DeserializeBool();
            FromPosX = deserializer.DeserializeF32();
            FromPosY = deserializer.DeserializeF32();
            FromPosZ = deserializer.DeserializeF32();
            ToPosX = deserializer.DeserializeF32();
            ToPosY = deserializer.DeserializeF32();
            ToPosZ = deserializer.DeserializeF32();
            Time = deserializer.DeserializeU32();
            CutType = deserializer.DeserializeU8();
        }

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

        void Deserialize(Serde::IDeserializer& deserializer) {
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
            Type = deserializer.DeserializeU32();
            Radius = deserializer.DeserializeF32();
        }

        float X;
        float Y;
        float Z;
        uint32_t Type;
        float Radius;
    };

    struct CSendDeathMessage final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 55)

        void Deserialize(Serde::IDeserializer& deserializer) {
            KillerID = deserializer.DeserializeU16();
            PlayerID = deserializer.DeserializeU16();
            Reason = deserializer.DeserializeU8();
        }

        uint16_t KillerID;
        uint16_t PlayerID;
        uint8_t Reason;
    };

    struct CSendGameTimeUpdate final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 60)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Time = deserializer.DeserializeI32();
        }

        int32_t Time;
    };

    struct CSendClientMessage final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 93)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Color = deserializer.DeserializeU32();
            uint32_t messageLength = deserializer.DeserializeU32();

            Message.resize(messageLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Message.data()), messageLength);
        }

        uint32_t Color;
        std::string Message;
    };

    struct CSetShopName final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 33)

        void Deserialize(Serde::IDeserializer& deserializer) {
            uint32_t length = deserializer.DeserializeU32();

            Name.resize(length);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Name.data()), length);
        }

        std::string Name;
    };

    struct CSetPlayerDrunkLevel final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 35)

        void Deserialize(Serde::IDeserializer& deserializer) {
            DrunkLevel = deserializer.DeserializeI32();
        }

        int32_t DrunkLevel;
    };

    struct CSetPlayerFightingStyle final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 89)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            FightStyle = deserializer.DeserializeU8();
        }

        uint16_t PlayerID;
        uint8_t FightStyle;
    };

    struct CSetInterior final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 156)

        void Deserialize(Serde::IDeserializer& deserializer) {
            InteriorID = deserializer.DeserializeU8();
        }

        uint8_t InteriorID;
    };

    struct CSetPlayerColor final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 72)

        void Deserialize(Serde::IDeserializer& deserializer) {
            PlayerID = deserializer.DeserializeU16();
            Color = deserializer.DeserializeU32();
        }

        uint16_t PlayerID;
        uint32_t Color;
    };

    struct CForceClassSelection final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 74)

        void Deserialize(Serde::IDeserializer& deserializer) {}
    };

    struct CToggleWidescreen final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 111)

        void Deserialize(Serde::IDeserializer& deserializer) {
            Enable = deserializer.DeserializeU8();
        }

        uint8_t Enable;
    };

    struct CSetPlayerWantedLevel final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 133)

        void Deserialize(Serde::IDeserializer& deserializer) {
            WantedLevel = deserializer.DeserializeU8();
        }

        uint8_t WantedLevel;
    };

    struct CSetCameraPos final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 157)

        void Deserialize(Serde::IDeserializer& deserializer) {
            LookPosX = deserializer.DeserializeF32();
            LookPosY = deserializer.DeserializeF32();
            LookPosZ = deserializer.DeserializeF32();
        }

        float LookPosX;
        float LookPosY;
        float LookPosZ;
    };

    struct CSetCameraLookAt final : public Serde::IDeserializable {
        LUNA_DEFINE_PACKET(true, 158)

        void Deserialize(Serde::IDeserializer& deserializer) {
            LookPosX = deserializer.DeserializeF32();
            LookPosY = deserializer.DeserializeF32();
            LookPosZ = deserializer.DeserializeF32();
            CutType = deserializer.DeserializeU8();
        }

        float LookPosX;
        float LookPosY;
        float LookPosZ;
        uint8_t CutType;
    };
}
