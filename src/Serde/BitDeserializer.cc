// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#include <Luna/Serde/BitSerde.hh>
#include <cmath>
#include <cstring>

using namespace Luna;
using namespace Luna::Serde;

class CNoBitsLeftException : public CSerdeException {
public:
    const char* what() const noexcept {
        return "no bits left to deserialize/skip";
    }
};

void CBitDeserializer::DeserializeBits(uint8_t* dest, size_t lengthInBits) {
    if (m_OffsetInBits + lengthInBits > m_DataSizeInBits)
        throw CNoBitsLeftException();

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

void CBitDeserializer::DeserializeBytes(uint8_t* dest, size_t length) {
    if ((m_OffsetInBits % 8) != 0)
        return DeserializeBits(dest, length * 8);

    #ifndef NDEBUG
    if (m_OffsetInBits + length * 8 > m_DataSizeInBits)
        throw CNoBitsLeftException();
    #endif

    memcpy(dest, m_Data + (m_OffsetInBits >> 3), length);
    m_OffsetInBits += length * 8;
}

void CBitDeserializer::SkipBytes(size_t count) {
    if (m_OffsetInBits + count * 8 > m_DataSizeInBits)
        throw CNoBitsLeftException();

    m_OffsetInBits += count * 8;
}

bool CBitDeserializer::DeserializeBool() {
    if (m_OffsetInBits + 1 > m_DataSizeInBits)
        throw CNoBitsLeftException();

    bool value = static_cast<bool>(m_Data[m_OffsetInBits >> 3] & (0x80 >> (m_OffsetInBits % 8)));
    m_OffsetInBits += 1;

    return value;
}
