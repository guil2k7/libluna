// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

namespace Luna::Core {
    template<typename T, typename U>
    inline constexpr auto CeilDiv(T n, U d) -> decltype(n / d) {
        return (n) ?
            ((n - static_cast<T>(1))) / d + (static_cast<decltype(n / d)>(1)) :
            static_cast<decltype(n / d)>(0)
        ;
    }
}
