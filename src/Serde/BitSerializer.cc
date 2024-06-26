// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Serde/BitSerde.hh>
#include <cstring>

using namespace Luna;
using namespace Luna::Serde;

class CNoBytesLeftException : public CSerdeException {
public:
    const char* what() const noexcept {
        return "no bytes left to serialize";
    }
};

void CBitSerializer::SerializeBits(uint8_t const* bits, size_t lengthInBits) {
    #ifndef NDEBUG
    if (BitsToBytes(m_OffsetInBits + lengthInBits) > m_Capacity)
        throw CNoBytesLeftException();
    #endif

    size_t offsetMod8 = m_OffsetInBits % 8;
    size_t bitsToWrite = lengthInBits;
    size_t writtenBits = 0;

    while (bitsToWrite > 0) {
        uint8_t byte = bits[writtenBits >> 3];

        if (bitsToWrite < 8)
            byte <<= 8 - bitsToWrite;

        if (offsetMod8 != 0) {
            m_Data[m_OffsetInBits >> 3] |= byte >> offsetMod8;

            if (8 - offsetMod8 < bitsToWrite)
                m_Data[(m_OffsetInBits >> 3) + 1] = byte << (8 - offsetMod8);
        }
        else {
            m_Data[m_OffsetInBits >> 3] = byte;
        }

        if (bitsToWrite >= 8) {
            m_OffsetInBits += 8;
            writtenBits += 8;
            bitsToWrite -= 8;
        }
        else {
            m_OffsetInBits += bitsToWrite;
            writtenBits += bitsToWrite;
            bitsToWrite = 0;
        }
    }
}

void CBitSerializer::SerializeBytes(uint8_t const* bytes, size_t length) {
    if ((m_OffsetInBits % 8) != 0)
        return SerializeBits(bytes, length * 8);

    #ifndef NDEBUG
    if (BitsToBytes(m_OffsetInBits) + length > m_Capacity)
        throw CNoBytesLeftException();
    #endif

    memcpy(m_Data + (m_OffsetInBits >> 3), bytes, length);
    m_OffsetInBits += length * 8;
}

void CBitSerializer::SerializeBool(bool value) {
    #ifndef NDEBUG
    if (BitsToBytes(m_OffsetInBits + 1) > m_Capacity)
        throw CNoBytesLeftException();
    #endif

    size_t offsetMod8 = m_OffsetInBits % 8;

    if (value) {
        if (offsetMod8 == 0)
            m_Data[m_OffsetInBits >> 3] = 0x80;
        else
            m_Data[m_OffsetInBits >> 3] |= 0x80 >> offsetMod8;
    }
    else {
        if (offsetMod8 == 0)
            m_Data[m_OffsetInBits >> 3] = 0;
        else
            m_Data[m_OffsetInBits >> 3] &= ~(0x80 >> offsetMod8);
    }

    m_OffsetInBits += 1;
}
