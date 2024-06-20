// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <string_view>

namespace Luna::Network {
    std::string_view GenerateAuthKey(std::string_view recvdKey);
}