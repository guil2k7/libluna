// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

namespace Luna::Network::Code {

inline void CStatsUpdate::Serialize(Serde::ISerializer& serializer) const {
    serializer.SerializeI32(Money);
    serializer.SerializeI32(DrunkLevel);
}

inline void COnFootSync::Serialize(Serde::ISerializer& serializer) const {
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

inline void COnFootSync::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();

    if (deserializer.DeserializeBool())
        LeftRight = deserializer.DeserializeI16();

    if (deserializer.DeserializeBool())
        UpDown = deserializer.DeserializeI16();

    Keys = deserializer.DeserializeU16();

    deserializer.DeserializeObject(Position);

    deserializer.DeserializeNormQuat(
        Rotation.W,
        Rotation.X,
        Rotation.Y,
        Rotation.Z
    );

    uint8_t health, armour;
    uint8_t healthArmour = deserializer.DeserializeU8();

    health = (health >> 4) & 0xF;
    armour = armour & 0xF;

    if (health == 0xF)
        Health = 100.0f;
    else if (health == 0)
        Health = 0.0f;
    else
        Health = health * 7.0f;

    if (armour == 0xF)
        Armour = 100.0f;
    else if (armour == 0)
        Armour = 0.0f;
    else
        Armour = armour * 7.0f;

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

inline void CSetPlayerFacingAngle::Deserialize(Serde::IDeserializer& deserializer) {
    Angle = deserializer.DeserializeF32();
}

inline void CServerJoin::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    Color = deserializer.DeserializeU32();
    IsNPC = deserializer.DeserializeU8();

    uint8_t playerNameLength = deserializer.DeserializeU8();
    PlayerName.resize(playerNameLength);
    deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(PlayerName.data()), playerNameLength);
}

inline void CServerQuit::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    reason = static_cast<eServerQuitReason>(deserializer.DeserializeU8());
}

inline void CSendSpawn::Serialize(Serde::ISerializer& serializer) const {
    // Nothing to serialize.
}

inline void CRequestClass::Serialize(Serde::ISerializer& serializer) const {
    serializer.SerializeU16(ID);
}

inline void CRequestSpawn::Serialize(Serde::ISerializer& serializer) const {
    // Nothing to serialize.
}

inline void CInitGame::Deserialize(Serde::IDeserializer& deserializer) {
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

inline void CUpdateScoresAndPings::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    Score = deserializer.DeserializeI32();
    Ping = deserializer.DeserializeU32();
}

inline void CClientCheck::Deserialize(Serde::IDeserializer& deserializer) {
    Type = deserializer.DeserializeU8();
    Address = deserializer.DeserializeU32();
    Offset = deserializer.DeserializeU16();
    Count = deserializer.DeserializeU16();
}

inline void CGameModeRestart::Deserialize(Serde::IDeserializer& deserializer) {
    // Nothing to deserialize.
}

inline void CApplyPlayerAnimation::Deserialize(Serde::IDeserializer& deserializer) {
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

inline void CClearPlayerAnimation::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
}

inline void CDeathBroadcast::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
}

inline void CSetPlayerName::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    uint8_t nameLength = deserializer.DeserializeU8();

    Name.resize(nameLength);
    deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Name.data()), nameLength);

    Success = deserializer.DeserializeU8();
}

inline void CSetPlayerPos::Deserialize(Serde::IDeserializer& deserializer) {
    deserializer.DeserializeObject(Position);
}

inline void CSetPlayerPosFindZ::Deserialize(Serde::IDeserializer& deserializer) {
    X = deserializer.DeserializeF32();
    Y = deserializer.DeserializeF32();
    Z = deserializer.DeserializeF32();
}

inline void CSetPlayerSkillLevel::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    SkillID = deserializer.DeserializeU32();
    Level = deserializer.DeserializeU16();
}

inline void CSetPlayerSkin::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU32();
    SkinID = deserializer.DeserializeU32();
}

inline void CSetPlayerTime::Deserialize(Serde::IDeserializer& deserializer) {
    Hour = deserializer.DeserializeU8();
    Minute = deserializer.DeserializeU8();
}

inline void CSetPlayerSpecialAction::Deserialize(Serde::IDeserializer& deserializer) {
    ActionID = deserializer.DeserializeU8();
}

inline void CSetWeather::Deserialize(Serde::IDeserializer& deserializer) {
    WeatherID = deserializer.DeserializeU8();
}

inline void CSetWorldBounds::Deserialize(Serde::IDeserializer& deserializer) {
    MaxX = deserializer.DeserializeF32();
    MinX = deserializer.DeserializeF32();
    MaxY = deserializer.DeserializeF32();
    MinY = deserializer.DeserializeF32();
}

inline void CSetPlayerVelocity::Deserialize(Serde::IDeserializer& deserializer) {
    X = deserializer.DeserializeF32();
    Y = deserializer.DeserializeF32();
    Z = deserializer.DeserializeF32();
}

inline void CTogglePlayerControllable::Deserialize(Serde::IDeserializer& deserializer) {
    Moveable = deserializer.DeserializeU8();
}

inline void CTogglePlayerSpectating::Deserialize(Serde::IDeserializer& deserializer) {
    Spectating = deserializer.DeserializeU32();
}

inline void CToggleClock::Deserialize(Serde::IDeserializer& deserializer) {
    Toggle = deserializer.DeserializeU8();
}

inline void CSetPlayerTeam::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    TeamID = deserializer.DeserializeU8();
}

inline void CPlaySound::Deserialize(Serde::IDeserializer& deserializer) {
    SoundID = deserializer.DeserializeU32();
    X = deserializer.DeserializeF32();
    Y = deserializer.DeserializeF32();
    Z = deserializer.DeserializeF32();
}

inline void CGivePlayerMoney::Deserialize(Serde::IDeserializer& deserializer) {
    Money = deserializer.DeserializeI32();
}

inline void CResetPlayerMoney::Deserialize(Serde::IDeserializer& deserializer) {
    // Nothing to deserialize.
}

inline void CResetPlayerWeapons::Deserialize(Serde::IDeserializer& deserializer) {
    // Nothing to deserialize.
}

inline void CGivePlayerWeapon::Deserialize(Serde::IDeserializer& deserializer) {
    WeaponID = deserializer.DeserializeU32();
    Bullets = deserializer.DeserializeU32();
}

inline void CPlayAudioStream::Deserialize(Serde::IDeserializer& deserializer) {
    uint8_t urlLength = deserializer.DeserializeU8();

    Url.resize(urlLength);
    deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Url.data()), urlLength);
    X = deserializer.DeserializeF32();
    Y = deserializer.DeserializeF32();
    Z = deserializer.DeserializeF32();
    Radius = deserializer.DeserializeF32();
    UsePos = deserializer.DeserializeU8();
}

inline void CPlayCrimeReport::Deserialize(Serde::IDeserializer& deserializer) {
    SuspectID = deserializer.DeserializeU16();
    InVehicle = deserializer.DeserializeU32();
    VehicleModel = deserializer.DeserializeU32();
    VehicleColor = deserializer.DeserializeU32();
    Crime = deserializer.DeserializeU32();
    X = deserializer.DeserializeF32();
    Y = deserializer.DeserializeF32();
    Z = deserializer.DeserializeF32();
}

inline void CStopAudioStream::Deserialize(Serde::IDeserializer& deserializer) {
    // Nothing to deserialize.
}

inline void CRemoveBuilding::Deserialize(Serde::IDeserializer& deserializer) {
    ObjectModel = deserializer.DeserializeU32();
    X = deserializer.DeserializeF32();
    Y = deserializer.DeserializeF32();
    Z = deserializer.DeserializeF32();
    Radius = deserializer.DeserializeF32();
}

inline void CSetPlayerHealth::Deserialize(Serde::IDeserializer& deserializer) {
    Health = deserializer.DeserializeF32();
}

inline void CSetPlayerArmour::Deserialize(Serde::IDeserializer& deserializer) {
    Armour = deserializer.DeserializeF32();
}

inline void CSetWeaponAmmo::Deserialize(Serde::IDeserializer& deserializer) {
    WeaponID = deserializer.DeserializeU8();
    Ammo = deserializer.DeserializeU16();
}

inline void CSetCameraBehind::Deserialize(Serde::IDeserializer& deserializer) {
    // Nothing to deserialize.
}

inline void CSetArmedWeapon::Deserialize(Serde::IDeserializer& deserializer) {
    WeaponID = deserializer.DeserializeU32();
}

inline void CWorldPlayerAdd::Deserialize(Serde::IDeserializer& deserializer) {
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

inline void CWorldPlayerRemove::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
}

inline void CInterpolateCamera::Deserialize(Serde::IDeserializer& deserializer) {
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

inline void CCreateExplosion::Deserialize(Serde::IDeserializer& deserializer) {
    X = deserializer.DeserializeF32();
    Y = deserializer.DeserializeF32();
    Z = deserializer.DeserializeF32();
    Type = deserializer.DeserializeU32();
    Radius = deserializer.DeserializeF32();
}

inline void CSendDeathMessage::Deserialize(Serde::IDeserializer& deserializer) {
    KillerID = deserializer.DeserializeU16();
    PlayerID = deserializer.DeserializeU16();
    Reason = deserializer.DeserializeU8();
}

inline void CSendGameTimeUpdate::Deserialize(Serde::IDeserializer& deserializer) {
    Time = deserializer.DeserializeI32();
}

inline void CSendClientMessage::Deserialize(Serde::IDeserializer& deserializer) {
    Color = deserializer.DeserializeU32();
    uint32_t messageLength = deserializer.DeserializeU32();

    Message.resize(messageLength);
    deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Message.data()), messageLength);
}

inline void CSetShopName::Deserialize(Serde::IDeserializer& deserializer) {
    uint32_t length = deserializer.DeserializeU32();

    Name.resize(length);
    deserializer.DeserializeBytes(reinterpret_cast<uint8_t*>(Name.data()), length);
}

inline void CSetPlayerDrunkLevel::Deserialize(Serde::IDeserializer& deserializer) {
    DrunkLevel = deserializer.DeserializeI32();
}

inline void CSetPlayerFightingStyle::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    FightStyle = deserializer.DeserializeU8();
}

inline void CSetInterior::Deserialize(Serde::IDeserializer& deserializer) {
    InteriorID = deserializer.DeserializeU8();
}

inline void CSetPlayerColor::Deserialize(Serde::IDeserializer& deserializer) {
    PlayerID = deserializer.DeserializeU16();
    Color = deserializer.DeserializeU32();
}

inline void CForceClassSelection::Deserialize(Serde::IDeserializer& deserializer) {
    // Nothing to deserialize.
}

inline void CToggleWidescreen::Deserialize(Serde::IDeserializer& deserializer) {
    Enable = deserializer.DeserializeU8();
}

inline void CSetPlayerWantedLevel::Deserialize(Serde::IDeserializer& deserializer) {
    WantedLevel = deserializer.DeserializeU8();
}

inline void CSetCameraPos::Deserialize(Serde::IDeserializer& deserializer) {
    LookPosX = deserializer.DeserializeF32();
    LookPosY = deserializer.DeserializeF32();
    LookPosZ = deserializer.DeserializeF32();
}

inline void CSetCameraLookAt::Deserialize(Serde::IDeserializer& deserializer) {
    LookPosX = deserializer.DeserializeF32();
    LookPosY = deserializer.DeserializeF32();
    LookPosZ = deserializer.DeserializeF32();
    CutType = deserializer.DeserializeU8();
}

} // namespace Luna::Network::Code
