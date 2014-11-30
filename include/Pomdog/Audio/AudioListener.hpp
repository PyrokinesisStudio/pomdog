﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_AUDIOLISTENER_C5B766B1_A5C8_444F_96C6_30CFF18CCF91_HPP
#define POMDOG_AUDIOLISTENER_C5B766B1_A5C8_444F_96C6_30CFF18CCF91_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "Pomdog/Math/Vector3.hpp"

namespace Pomdog {

class AudioListener {
public:
	Vector3 Forward;
	Vector3 Position;
	Vector3 Up;
	Vector3 Velocity;
};

}// namespace Pomdog

#endif // !defined(POMDOG_AUDIOLISTENER_C5B766B1_A5C8_444F_96C6_30CFF18CCF91_HPP)