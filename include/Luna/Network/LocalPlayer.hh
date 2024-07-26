// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include "Client.hh"

namespace Luna::Network {

class CLocalPlayerComponent {
public:
    void Install(CClient& client);

private:
    void ProcessSetPlayerPos(CClient& client, uint8_t const* rawData, size_t bitSize);
};

} // namespace Luna::Network
