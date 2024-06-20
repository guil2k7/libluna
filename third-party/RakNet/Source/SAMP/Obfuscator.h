#pragma once

#include <cstdint>
#include <cstddef>

namespace RakNet::SAMP
{
    /// Obfuscates the data to make it difficult to read.
    /// **Info**: the pointer to the destination buffer can be the same as to the source buffer. 
    /// **Warning**: the length of the destination buffer must be `len + 1` to store the checksum.
    ///
    /// # Example
    /// ```
    /// uint8_t buf[4 + 1];
    /// *reinterpret_cast<uint32_t*>(&buf[0]) = 0xFFFFFFFF;
    ///
    /// Obfuscate(buf, buf, 4, 7777);
    /// ```
    void Obfuscate(uint8_t* dest, const uint8_t* src, size_t len, uint32_t salt);
}
