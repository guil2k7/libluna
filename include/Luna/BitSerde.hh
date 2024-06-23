// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>
#include <cstddef>

namespace Luna::BitSerde {
    static inline size_t BitsToBytes(size_t value) {
        return (value + 7) >> 3;
    }

    static inline size_t BytesToBits(size_t value) {
        return value << 3;
    }

    class CSerializer {
    public:
        CSerializer(uint8_t* data, size_t capacity) :
            m_Data(data), m_Capacity(capacity), m_OffsetInBits(0) {}

        void SerializeBits(uint8_t const* bits, size_t lengthInBits);
        void SerializeBytes(uint8_t const* bytes, size_t length);
        void SerializeBool(bool value);

        inline void SerializeU8(uint8_t value)   { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 1); }
        inline void SerializeU16(uint16_t value) { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 2); }
        inline void SerializeU32(uint32_t value) { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 4); }
        inline void SerializeU64(uint64_t value) { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 8); }
        inline void SerializeI8(int8_t value)    { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 1); }
        inline void SerializeI16(int16_t value)  { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 2); }
        inline void SerializeI32(int32_t value)  { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 4); }
        inline void SerializeI64(int64_t value)  { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 8); }
        inline void SerializeF32(float value)    { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 4); }
        inline void SerializeF64(double value)   { SerializeBytes(reinterpret_cast<uint8_t*>(&value), 8); }

        template<typename T>
        inline void SerializeObject(T const& object) {
            object.Serialize(*this);
        }

        /// Returns the offset in bytes.
        inline size_t OffsetInBytes() const {
            return BitsToBytes(m_OffsetInBits);
        }

        /// Returns the offset in bits.
        inline size_t OffsetInBits() const {
            return m_OffsetInBits;
        }

    private:
        uint8_t* m_Data;
        size_t m_Capacity;
        size_t m_OffsetInBits;
    };

    class CDeserializer {
    public:
        CDeserializer(uint8_t const* data, size_t length) :
            m_Data(data), m_Length(length), m_OffsetInBits(0) {}

        void DeserializeBits(uint8_t* dest, size_t lengthInBits);
        void DeserializeBytes(uint8_t* dest, size_t length);
        void SkipBytes(size_t count);
        bool DeserializeBool();

        inline uint8_t DeserializeU8()   { uint8_t x;  DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 1); return x; }
        inline uint16_t DeserializeU16() { uint16_t x; DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 2); return x; }
        inline uint32_t DeserializeU32() { uint32_t x; DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 4); return x; }
        inline uint64_t DeserializeU64() { uint64_t x; DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 8); return x; }
        inline int8_t DeserializeI8()    { int8_t x;   DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 1); return x; }
        inline int16_t DeserializeI16()  { int16_t x;  DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 2); return x; }
        inline int32_t DeserializeI32()  { int32_t x;  DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 4); return x; }
        inline int64_t DeserializeI64()  { int64_t x;  DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 8); return x; }
        inline float DeserializeF32()    { float x;    DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 4); return x; }
        inline double DeserializeF64()   { double x;   DeserializeBytes(reinterpret_cast<uint8_t*>(&x), 8); return x; }

        template<typename T>
        inline void DeserializeObject(T& object) {
            object.Deserialize(*this);
        }

        /// Returns the offset in bytes.
        inline size_t OffsetInBytes() const {
            return BitsToBytes(m_OffsetInBits);
        }

        /// Returns the offset in bits.
        inline size_t OffsetInBits() const {
            return m_OffsetInBits;
        }

    private:
        uint8_t const* m_Data;
        size_t m_Length;
        size_t m_OffsetInBits;
    };

    struct ISerializable {
        virtual void Serialize(BitSerde::CSerializer& serializer) const = 0;
    };

    struct IDeserializable {
        virtual void Deserialize(BitSerde::CDeserializer& deserializer) = 0;
    };
}
