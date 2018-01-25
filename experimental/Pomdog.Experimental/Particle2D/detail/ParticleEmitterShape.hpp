// Copyright (c) 2013-2018 mogemimi. Distributed under the MIT license.

#pragma once

#include "Pomdog/Math/Vector2.hpp"
#include "Pomdog/Math/Radian.hpp"
#include <random>

namespace Pomdog {
namespace Detail {
namespace Particles {

class ParticleEmitterShape {
public:
    virtual ~ParticleEmitterShape() = default;

    virtual void Compute(std::mt19937 & random, Vector2 & emitPosition, Radian<float> & emitAngle) const = 0;
};

} // namespace Particles
} // namespace Detail
} // namespace Pomdog
