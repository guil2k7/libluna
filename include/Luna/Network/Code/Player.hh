// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "../Packet.hh"
#include "../../Game/Vector.hh"
#include <cstdint>
#include <string>

namespace Luna::Network::Code {
    enum eServerQuitReason : uint8_t {
        SERVER_QUIT_REASON_TIMEOUT,
        SERVER_QUIT_REASON_QUIT,
        SERVER_QUIT_REASON_KICK_OR_BAN,
    };

    struct CAimSync final : public IPacketSerializable {
        LUNA_DEFINE_PACKET(20, false)

        void Serialize(BitSerde::CSerializer& serializer) const override {
            serializer.SerializeU8(CamMode);
            serializer.SerializeObject(CamFront);
            serializer.SerializeObject(CamPos);
            serializer.SerializeF32(AimZ);
            serializer.SerializeU8(WeaponState << 6 | CamZoom);
            serializer.SerializeU8(AspectRatio);
        }

        uint8_t CamMode;
        Game::CVector CamFront;
        Game::CVector CamPos;
        float AimZ;
        uint8_t WeaponState : 2;
        uint8_t CamZoom : 6;
        uint8_t AspectRatio;
    };

    // TODO: 
    // struct CWeaponsUpdate final : public IPacketSerializable {
    //     LUNA_DEFINE_PACKET(204, false)

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

    struct CStatsUpdate final : public IPacketSerializable {
        LUNA_DEFINE_PACKET(205, false)

        void Serialize(BitSerde::CSerializer& serializer) const override {
            serializer.SerializeI32(Money);
            serializer.SerializeI32(DrunkLevel);
        }

        int32_t Money;
        int32_t DrunkLevel;
    };

    struct CBulletSync final : public IPacketSerializable {
        LUNA_DEFINE_PACKET(206, false)

        void Serialize(BitSerde::CSerializer& serializer) const override {
            serializer.SerializeU8(HitType);
            serializer.SerializeU16(HitID);
            serializer.SerializeObject(Origin);
            serializer.SerializeObject(HitPos);
            serializer.SerializeObject(Offset);
            serializer.SerializeF32(WeaponID);
        }

        uint8_t HitType;
        uint16_t HitID;
        Game::CVector Origin;
        Game::CVector HitPos;
        Game::CVector Offset;
        uint8_t WeaponID;
    };

    struct COnFootSync final : public IPacketSerializable {
        LUNA_DEFINE_PACKET(207, false)

        void Serialize(BitSerde::CSerializer& serializer) const override {
            serializer.SerializeU16(LrKey);
            serializer.SerializeU16(UdKey);
            serializer.SerializeU16(Keys);
            serializer.SerializeObject(Pos);
            serializer.SerializeU8(Health);
            serializer.SerializeU8(Armour);
            serializer.SerializeU8(AdditionalKey << 6 | WeaponId);
            serializer.SerializeU8(SpecialAction);
            serializer.SerializeObject(Velocity);
            serializer.SerializeObject(SurfingOffsets);
            serializer.SerializeI16(AnimationID);
            serializer.SerializeI16(AnimationFlags);
        }

        uint16_t LrKey;
        uint16_t UdKey;
        uint16_t Keys;
        Game::CVector Pos;
        Game::CVector4D quat;
        uint8_t Health;
        uint8_t Armour;
        uint8_t AdditionalKey : 2;
        uint8_t WeaponId : 6;
        uint8_t SpecialAction;
        Game::CVector Velocity;
        Game::CVector SurfingOffsets;
        uint16_t SurfingVehicleID;
        int16_t AnimationID;
        int16_t AnimationFlags;
    };

    // TODO: Move to vehicle component.
    // struct CUnoccupiedSync final : public IPacketSerializable {
    //     LUNA_DEFINE_PACKET(209, false)

    //     uint16_t VehicleID;
    //     uint8_t SeatID;
    //     Game::CVector Roll;
    //     Game::CVector Direction;
    //     Game::CVector Pos;
    //     Game::CVector AngularVelocity;
    //     float VehicleHealth;
    // };

    // TODO: Move to vehicle component.
    // struct CTrailerSync final : public IPacketSerializable {
    //     LUNA_DEFINE_PACKET(210, false)

    //     uint16_t TrailerID;
    //     Game::CVector Pos;
    //     Game::CVector4D quat;
    //     Game::CVector Velocity;
    //     Game::CVector AngularVelocity;
    // };

    // struct CPassengerSync final : public IPacketSerializable {
    //     LUNA_DEFINE_PACKET(211, false)

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

    struct CSpectatingSync final : public IPacketSerializable {
        LUNA_DEFINE_PACKET(212, false)

        void Serialize(BitSerde::CSerializer& serializer) const override {
            serializer.SerializeU16(LrKey);
            serializer.SerializeU16(UdKey);
            serializer.SerializeU16(Keys);
            serializer.SerializeObject(Pos);
        }
        
        uint16_t LrKey;
        uint16_t UdKey;
        uint16_t Keys;
        Game::CVector Pos;
    };

    struct CSetPlayerFacingAngle final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(19, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Angle = deserializer.DeserializeF32();
        }

        float Angle;
    };

    struct CServerJoin final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(137, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CServerQuit final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(138, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
            reason = static_cast<eServerQuitReason>(deserializer.DeserializeU8());
        }

        uint16_t PlayerID;
        eServerQuitReason reason;
    };

    struct CInitGame final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(139, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CUpdateScoresAndPings final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(155, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
            Score = deserializer.DeserializeI32();
            Ping = deserializer.DeserializeU32();
        }

        uint16_t PlayerID;
        int32_t Score;
        uint32_t Ping;
    };

    struct CClientCheck final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(103, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CGameModeRestart final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(40, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {}

        // Additional Information: This RPC reconnects a player to the server showing him "The server is restarting..." message.
    };

    struct CApplyPlayerAnimation final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(86, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CClearPlayerAnimation final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(87, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
    };

    struct CDeathBroadcast final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(166, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
    };

    struct CSetPlayerName final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(11, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CSetPlayerPos final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(12, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

        float X;
        float Y;
        float Z;
    };

    struct CSetPlayerPosFindZ final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(13, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

        float X;
        float Y;
        float Z;
    };

    struct CSetPlayerSkillLevel final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(34, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
            SkillID = deserializer.DeserializeU32();
            Level = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
        uint32_t SkillID;
        uint16_t Level;
    };

    struct CSetPlayerSkin final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(153, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU32();
            SkinID = deserializer.DeserializeU32();
        }

        uint32_t PlayerID;
        uint32_t SkinID;
    };

    struct CSetPlayerTime final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(29, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Hour = deserializer.DeserializeU8();
            Minute = deserializer.DeserializeU8();
        }

        uint8_t Hour;
        uint8_t Minute;
    };

    struct CSetPlayerSpecialAction final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(88, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            ActionID = deserializer.DeserializeU8();
        }

        uint8_t ActionID;
    };

    struct CSetWeather final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(152, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            WeatherID = deserializer.DeserializeU8();
        }

        uint8_t WeatherID;
    };

    struct CSetWorldBounds final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(17, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CSetPlayerVelocity final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(90, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            X = deserializer.DeserializeF32();
            Y = deserializer.DeserializeF32();
            Z = deserializer.DeserializeF32();
        }

        float X;
        float Y;
        float Z;
    };

    struct CTogglePlayerControllable final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(15, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Moveable = deserializer.DeserializeU8();
        }

        bool Moveable;
    };

    struct CTogglePlayerSpectating final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(124, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Spectating = deserializer.DeserializeU32();
        }

        bool Spectating;
    };

    struct CToggleClock final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(30, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Toggle = deserializer.DeserializeU8();
        }

        bool Toggle;
    };

    struct CSetPlayerTeam final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(69, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
            TeamID = deserializer.DeserializeU8();
        }

        uint16_t PlayerID;
        uint8_t TeamID;
    };

    struct CPlaySound final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(16, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CGivePlayerMoney final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(18, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Money = deserializer.DeserializeI32();
        }

        int32_t Money;
    };

    struct CResetPlayerMoney final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(20, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {}
    };

    struct CResetPlayerWeapons final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(21, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {}
    };

    struct CGivePlayerWeapon final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(22, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            WeaponID = deserializer.DeserializeU32();
            Bullets = deserializer.DeserializeU32();
        }

        uint32_t WeaponID;
        uint32_t Bullets;
    };

    struct CPlayAudioStream final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(41, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CPlayCrimeReport final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(112, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CStopAudioStream final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(42, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {}
    };

    struct CRemoveBuilding final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(43, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CSetPlayerHealth final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(14, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Health = deserializer.DeserializeF32();
        }

        float Health;
    };

    struct CSetPlayerArmour final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(66, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Armour = deserializer.DeserializeF32();
        }

        float Armour;
    };

    struct CSetWeaponAmmo final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(145, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            WeaponID = deserializer.DeserializeU8();
            Ammo = deserializer.DeserializeU16();
        }

        uint8_t WeaponID;
        uint16_t Ammo;
    };

    struct CSetCameraBehind final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(162, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {}
    };

    struct CSetArmedWeapon final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(67, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            WeaponID = deserializer.DeserializeU32();
        }

        uint32_t WeaponID;
    };

    struct CWorldPlayerAdd final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(32, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CWorldPlayerRemove final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(163, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
        }

        uint16_t PlayerID;
    };

    struct CInterpolateCamera final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(82, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CCreateExplosion final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(79, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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

    struct CSendDeathMessage final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(55, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            KillerID = deserializer.DeserializeU16();
            PlayerID = deserializer.DeserializeU16();
            Reason = deserializer.DeserializeU8();
        }

        uint16_t KillerID;
        uint16_t PlayerID;
        uint8_t Reason;
    };

    struct CSendGameTimeUpdate final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(60, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Time = deserializer.DeserializeI32();
        }

        int32_t Time;
    };

    struct CSendClientMessage final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(93, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Color = deserializer.DeserializeU32();
            uint32_t messageLength = deserializer.DeserializeU32();

            Message.resize(messageLength);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Message.data()), messageLength);
        }

        uint32_t Color;
        std::string Message;
    };

    struct CSetShopName final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(33, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            uint32_t length = deserializer.DeserializeU32();

            Name.resize(length);
            deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Name.data()), length);
        }

        std::string Name;
    };

    struct CSetPlayerDrunkLevel final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(35, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            DrunkLevel = deserializer.DeserializeI32();
        }

        int32_t DrunkLevel;
    };

    struct CSetPlayerFightingStyle final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(89, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
            FightStyle = deserializer.DeserializeU8();
        }

        uint16_t PlayerID;
        uint8_t FightStyle;
    };

    struct CSetInterior final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(156, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            InteriorID = deserializer.DeserializeU8();
        }

        uint8_t InteriorID;
    };

    struct CSetPlayerColor final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(72, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            PlayerID = deserializer.DeserializeU16();
            Color = deserializer.DeserializeU32();
        }

        uint16_t PlayerID;
        uint32_t Color;
    };

    struct CForceClassSelection final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(74, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {}
    };

    struct CToggleWidescreen final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(111, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            Enable = deserializer.DeserializeU8();
        }

        uint8_t Enable;
    };

    struct CSetPlayerWantedLevel final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(133, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            WantedLevel = deserializer.DeserializeU8();
        }

        uint8_t WantedLevel;
    };

    struct CSetCameraPos final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(157, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
            LookPosX = deserializer.DeserializeF32();
            LookPosY = deserializer.DeserializeF32();
            LookPosZ = deserializer.DeserializeF32();
        }

        float LookPosX;
        float LookPosY;
        float LookPosZ;
    };

    struct CSetCameraLookAt final : public IPacketDeserializable {
        LUNA_DEFINE_PACKET(158, true)

        void Deserialize(BitSerde::CDeserializer& deserializer) override {
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
