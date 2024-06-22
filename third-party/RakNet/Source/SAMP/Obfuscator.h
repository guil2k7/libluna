#pragma once

#include <cstdint>
#include <cstddef>

namespace RakNet::SAMP
{
    void Obfuscate(uint8_t* dest, const uint8_t* src, size_t len, uint32_t salt);
}
