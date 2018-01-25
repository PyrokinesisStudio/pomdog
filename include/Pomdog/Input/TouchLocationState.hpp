// Copyright (c) 2013-2018 mogemimi. Distributed under the MIT license.

#pragma once

#include <cstdint>

namespace Pomdog {

enum class TouchLocationState : std::uint8_t {
    Invalid,
    Moved,
    Pressed,
    Released,
};

} // namespace Pomdog
