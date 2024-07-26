// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the BSD 3-Clause License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/bsd-3-clause.

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

    x = cx / 65535.0f;
    y = cy / 65535.0f;
    z = cz / 65535.0f;

    if (cxNeg) x = -x;
    if (cyNeg) y = -y;
    if (czNeg) z = -z;

    float difference = 1.0f - x * x - y * y - z * z;

    if (difference < 0.0f)
        difference = 0.0f;

    w = sqrt(difference);

    if (cwNeg) w = -w;
}

void IDeserializer::DeserializeCompressedVec(float& x, float& y, float& z) {
    float magnitude = DeserializeF32();

    if (magnitude == 0.0f) {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;

        return;
    }

    float cx = DeserializeCompressedF32();
    float cy = DeserializeCompressedF32();
    float cz = DeserializeCompressedF32();

    x = cx * magnitude;
    y = cy * magnitude;
    z = cz * magnitude;
}
