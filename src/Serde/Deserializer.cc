// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Serde/Serde.hh>
#include <cmath>

using namespace Luna;
using namespace Luna::Serde;

void IDeserializer::DeserializeNormQuat(float& w, float& x, float& y, float& z) {
    bool cwNeg = DeserializeBool();
    bool cxNeg = DeserializeBool();
    bool cyNeg = DeserializeBool();
    bool czNeg = DeserializeBool();

    uint16_t cx = DeserializeU16();
    uint16_t cy = DeserializeU16();
    uint16_t cz;

    try {
        cz = DeserializeU16();
    }
    catch (std::exception) {
        cz = 0;
    }

    x = cx / 65535.0F;
    y = cy / 65535.0F;
    z = cz / 65535.0F;

    if (cxNeg) x = -x;
    if (cyNeg) y = -y;
    if (czNeg) z = -z;

    float difference = 1.0F - x * x - y * y - z * z;

    if (difference < 0.0F)
        difference = 0.0F;

    w = sqrt(difference);

    if (cwNeg) w = -w;
}

void IDeserializer::DeserializeCompressedVec(float& x, float& y, float& z) {
    float magnitude = DeserializeF32();

    if (magnitude == 0.0F) {
        x = 0.0F;
        y = 0.0F;
        z = 0.0F;

        return;
    }

    float cx = DeserializeCompressedF32();
    float cy = DeserializeCompressedF32();
    float cz = DeserializeCompressedF32();

    x = cx * magnitude;
    y = cy * magnitude;
    z = cz * magnitude;
}
