// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/BitSerde.hh>
#include <cstring>
#include <exception>

using namespace Luna;
using namespace Luna::BitSerde;

struct CNoBytesLeft : public std::exception {
public:
    const char* what() const noexcept {
        return "no bytes left to deserialize/skip";
    }
};

void CDeserializer::DeserializeBits(uint8_t* dest, size_t lengthInBits) {
    if (BitsToBytes(m_OffsetInBits + lengthInBits) > m_Length)
        throw CNoBytesLeft();

    size_t offsetMod8 = m_OffsetInBits % 8;
    size_t bitsToRead = lengthInBits;
    size_t readBits = 0;

    while (bitsToRead > 0) {
        dest[readBits >> 3] = m_Data[m_OffsetInBits >> 3] << offsetMod8;

        if (offsetMod8 > 0 && bitsToRead > 8 - offsetMod8)
            dest[readBits >> 3] |= m_Data[(m_OffsetInBits >> 3) + 1] >> (8 - offsetMod8);

        if (bitsToRead >= 8) {
            m_OffsetInBits += 8;
            readBits += 8;
            bitsToRead -= 8;
        }
        else {
            dest[readBits >> 3] >>= bitsToRead;

            m_OffsetInBits += bitsToRead;
            readBits += bitsToRead;
            bitsToRead = 0;
        }
    }
}

void CDeserializer::DeserializeBytes(uint8_t* dest, size_t length) {
    if ((m_OffsetInBits % 8) != 0)
        return DeserializeBits(dest, length * 8);

    #ifndef NDEBUG
    if (BitsToBytes(m_OffsetInBits) + length > m_Length)
        throw CNoBytesLeft();
    #endif

    memcpy(dest, m_Data + (m_OffsetInBits >> 3), length);
    m_OffsetInBits += length * 8;
}

void CDeserializer::SkipBytes(size_t count) {
    if (BitsToBytes(m_OffsetInBits) + count > m_Length)
        throw CNoBytesLeft();

    m_OffsetInBits += count * 8;
}

bool CDeserializer::DeserializeBool() {
    if (BitsToBytes(m_OffsetInBits + 1) > m_Length)
        throw CNoBytesLeft();

    bool value = static_cast<bool>(m_Data[m_OffsetInBits >> 3] & (0x80 >> (m_OffsetInBits % 8)));
    m_OffsetInBits += 1;

    return value;
}

