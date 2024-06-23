#include "SAMP.h"
#include "RakAssert.h"
#include <cstring>

#define ROTL(value, shift) ((value << shift) | (value >> (sizeof (value) * 8 - shift)))
#define ROTR(value, shift) ((value >> shift) | (value << (sizeof (value) * 8 - shift)))

static inline uint16_t Swap16(uint16_t value) {
    return ((value >> 8) | (value << 8));
}

static inline uint32_t Swap32(uint32_t value) {
    return ((value >> 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0x0000FF00) | (value << 24));
}

static inline uint64_t Swap64(uint64_t value) {
    return
        ((value >> 56) | ((value << 40) & 0x00FF000000000000) |
        ((value << 24) & 0x0000FF0000000000) | ((value << 8)  & 0x000000FF00000000) |
        ((value >> 8)  & 0x00000000FF000000) | ((value >> 24) & 0x0000000000FF0000) |
        ((value >> 40) & 0x000000000000FF00) | (value << 56));
}

static void SHA1(uint32_t* out, char const* string, size_t stringLength) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    uint32_t const complement =
        (55 - (stringLength % 56)) + 8 * (((stringLength + 8) / 64));

    size_t const bufferSize = stringLength + complement + 8 + 1;

    uint8_t buffer[bufferSize];

    memcpy(buffer, string, stringLength);
    memset(buffer + stringLength + 1, 0, complement);

    buffer[stringLength] = 128;

    *reinterpret_cast<uint64_t*>(&buffer[stringLength + 1 + complement]) =
        Swap64(stringLength * 8);

    size_t const chunksCount = bufferSize / 64;
    uint32_t w[80];

    for (size_t i = 0; i < chunksCount; ++i) {
        for (size_t j = 0; j < 16; ++j)
            w[j] = Swap32(*reinterpret_cast<uint32_t*>(&buffer[i * 64 + j * 4]));

        memset(&w[16], 0, 64 * 4);

        for (size_t j = 16; j < 80; ++j)
            w[j] = ROTL((w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]), 1);

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for (size_t j = 0; j < 80; ++j) {
            uint32_t f, k;

            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t newA = (ROTL(a, 5) + f + e + k + w[j]);

            e = d;
            d = c;
            c = ROTL(b, 30);
            b = a;
            a = newA;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    out[0] = h0;
    out[1] = h1;
    out[2] = h2;
    out[3] = h3;
    out[4] = h4;
}

static uint8_t const AUTH_HASH_TRANSFORM_TABLE[100] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xE4, 0xB5, 0xB7, 0x0A, 0x00, 0x00, 0x00,
    0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B,
    0x13, 0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41,
    0x4D, 0x41, 0x00, 0x00, 0xB1, 0x8E, 0x7C, 0xFB, 0x51, 0x93, 0x00, 0x00,
    0x00, 0x20, 0x63, 0x48, 0x52, 0x4D, 0x00, 0x00, 0x7A, 0x25, 0x00, 0x00,
    0x80, 0x83, 0x00, 0x00, 0xF9, 0xFF, 0x00, 0x00, 0x80, 0xE9, 0x00, 0x00,
    0x75, 0x30, 0x00, 0x00
};

static uint8_t TransformAuthSHA1(uint8_t value, uint8_t salt) {
    uint8_t result = value;

    for (size_t i = 0; i < sizeof (AUTH_HASH_TRANSFORM_TABLE); ++i)
        result ^= AUTH_HASH_TRANSFORM_TABLE[i] ^ salt;

    return result;
}

static uint8_t const CANIMMANAGER_ADDANIMATION[20] = {
    0xFF, 0x25, 0x34, 0x39,
    0x4D, 0x00, 0x90, 0x90,
    0x90, 0x90, 0x56, 0x57,
    0x50, 0x8B, 0x44, 0x24,
    0x14, 0x8D, 0x0C, 0x80
};

static char HexDigitToChar(int digit) {
    if (digit > 9)
        return digit - 10 + 'A';

    return digit + '0';
}

static void StringifyHash(char* output, uint8_t const* hash) {
    for (size_t i = 0, j = 0; i < 20; ++i) {
        uint8_t byte = hash[i];

        *output++ = HexDigitToChar((byte >> 4) & 0xF);
        *output++ = HexDigitToChar(byte & 0xF);
    }
}

void RakNet::SAMP::GenerateAuthKey(char* output, char const* input, size_t inputLength) {
    uint8_t hash[20];
    SHA1(reinterpret_cast<uint32_t*>(&hash), input, inputLength);

    size_t i = 0;

    for (; i < 5; ++i)
        hash[i] = TransformAuthSHA1(hash[i], 0x2F);

    for (; i < 10; ++i)
        hash[i] = TransformAuthSHA1(hash[i], 0x45);

    for (; i < 15; ++i)
        hash[i] = TransformAuthSHA1(hash[i], 0x6F);

    for (; i < 20; ++i)
        hash[i] = TransformAuthSHA1(hash[i], 0xDB);

    for (i = 0; i < 20; ++i)
        hash[i] ^= CANIMMANAGER_ADDANIMATION[i];

    StringifyHash(output, hash);
}
