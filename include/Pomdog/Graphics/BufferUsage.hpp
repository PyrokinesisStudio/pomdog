﻿//
//  Copyright (C) 2013-2014 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_BUFFERUSAGE_E289E712_AF1F_4E88_A9E7_2E7BB5F1CB33_HPP
#define POMDOG_BUFFERUSAGE_E289E712_AF1F_4E88_A9E7_2E7BB5F1CB33_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

#include <cstdint>

namespace Pomdog {

///@~Japanese
/// @brief バッファの使用方法を定義します。
enum class BufferUsage: std::uint8_t {
	Immutable,
	Dynamic,
};

}// namespace Pomdog

#endif // !defined(POMDOG_BUFFERUSAGE_E289E712_AF1F_4E88_A9E7_2E7BB5F1CB33_HPP)
