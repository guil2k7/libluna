// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <cstdint>
#include <cstddef>
#include <exception>

namespace Luna::Serde {

class CSerdeException : public std::exception {};

class ISerializable {
public:
    virtual void Serialize(class ISerializer& serializer) const = 0;
};

class IDeserializable {
public:
    virtual void Deserialize(class IDeserializer& deserializer) = 0;
};

class ISerializer {
public:
    virtual void SerializeBytes(uint8_t const* bytes, size_t length) = 0;
    virtual void SerializeBool(bool value) = 0;
    virtual void SerializeU8(uint8_t value) = 0;
    virtual void SerializeU16(uint16_t value) = 0;
    virtual void SerializeU32(uint32_t value) = 0;
    virtual void SerializeU64(uint64_t value) = 0;
    virtual void SerializeI8(int8_t value) = 0;
    virtual void SerializeI16(int16_t value) = 0;
    virtual void SerializeI32(int32_t value) = 0;
    virtual void SerializeI64(int64_t value) = 0;
    virtual void SerializeF32(float value) = 0;
    virtual void SerializeF64(double value) = 0;
    virtual size_t OffsetInBytes() const = 0;

    inline void SerializeObject(ISerializable& object) {
        object.Serialize(*this);
    }

    template<typename T>
    inline void SerializeObject(T& object) {
        object.Serialize(*this);
    }
};

class IDeserializer {
public:
    virtual void DeserializeBytes(uint8_t* dest, size_t length) = 0;
    virtual void SkipBytes(size_t count) = 0;
    virtual bool DeserializeBool() = 0;
    virtual uint8_t DeserializeU8() = 0;
    virtual uint16_t DeserializeU16() = 0;
    virtual uint32_t DeserializeU32() = 0;
    virtual uint64_t DeserializeU64() = 0;
    virtual int8_t DeserializeI8() = 0;
    virtual int16_t DeserializeI16() = 0;
    virtual int32_t DeserializeI32() = 0;
    virtual int64_t DeserializeI64() = 0;
    virtual float DeserializeF32() = 0;
    virtual double DeserializeF64() = 0;
    virtual size_t OffsetInBytes() const = 0;

    inline void DeserializeObject(IDeserializable& object) {
        object.Deserialize(*this);
    }

    template<typename T>
    inline void DeserializeObject(T& object) {
        object.Deserialize(*this);
    }

    void DeserializeNormQuat(float& w, float& x, float& y, float& z);
    void DeserializeCompressedVec(float& x, float& y, float& z);

    inline float DeserializeCompressedF32() {
        return static_cast<float>(DeserializeU16()) / 32767.5F - 1.0f;
    }
};

} // namespace Luna::Serde
