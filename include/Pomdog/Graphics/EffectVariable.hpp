﻿//
//  Copyright (C) 2013-2014 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_EFFECTVARIABLE_B6867EDF_BF55_45D6_AB68_A610A5557AEA_HPP
#define POMDOG_EFFECTVARIABLE_B6867EDF_BF55_45D6_AB68_A610A5557AEA_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

#include "EffectAnnotation.hpp"
#include <cstdint>
#include <string>

namespace Pomdog {

///@~Japanese
/// @brief 定数バッファの要素です。
class EffectVariable {
public:
	std::string Name;
	EffectAnnotation Annotation;
	std::uint32_t StartOffset;
};

}// namespace Pomdog

#endif // !defined(POMDOG_EFFECTVARIABLE_B6867EDF_BF55_45D6_AB68_A610A5557AEA_HPP)
