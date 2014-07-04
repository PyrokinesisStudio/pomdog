﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_GAMEPADTYPE_7A74879B_88DF_4BDC_A1BE_46231883D9F8_HPP
#define POMDOG_GAMEPADTYPE_7A74879B_88DF_4BDC_A1BE_46231883D9F8_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <cstdint>

namespace Pomdog {

///@~Japanese
/// @brief ゲームパッドの種類を識別するのに使います。
enum class GamepadType: std::uint8_t {
	Unknown,
	Gamepad,
	ArcadeStick,
	DancePad,
	DrumKit,
	FlightStick,
	Xbox360Pad,
	XboxOnePad,
};

}// namespace Pomdog

#endif // !defined(POMDOG_GAMEPADTYPE_7A74879B_88DF_4BDC_A1BE_46231883D9F8_HPP)