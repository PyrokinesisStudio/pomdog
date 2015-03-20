﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_DEGREE_8B079286_FF3F_4EEC_BDD2_85D914A0B064_HPP
#define POMDOG_DEGREE_8B079286_FF3F_4EEC_BDD2_85D914A0B064_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "detail/TaggedArithmetic.hpp"

namespace Pomdog {
namespace Detail {
namespace Tags {

struct DegreeTag {};

}// namespace Tags
}// namespace Detail

template <typename T>
using Degree = Detail::TaggedArithmetic<T, Detail::Tags::DegreeTag>;

}// namespace Pomdog

#endif // !defined(POMDOG_DEGREE_8B079286_FF3F_4EEC_BDD2_85D914A0B064_HPP)
