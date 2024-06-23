#pragma once

#include <cstdint>
#include <cstddef>

namespace RakNet::SAMP
{
    void Obfuscate(uint8_t* dest, uint8_t const* src, size_t len, uint32_t salt);
    void GenerateAuthKey(char* output, char const* input, size_t inputLength);
}
