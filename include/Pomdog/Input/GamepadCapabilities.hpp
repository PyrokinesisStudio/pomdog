// Copyright (c) 2013-2018 mogemimi. Distributed under the MIT license.

#pragma once

#include "Pomdog/Input/GamepadType.hpp"
#include <cstdint>

namespace Pomdog {

struct GamepadCapabilities final {
    GamepadType GamepadType = GamepadType::Unknown;

    bool IsConnected = false;

    bool HasLeftXThumbStick = false;

    bool HasLeftYThumbStick = false;

    bool HasRightXThumbStick = false;

    bool HasRightYThumbStick = false;
};

} // namespace Pomdog
