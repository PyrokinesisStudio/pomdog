// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_SAMPLERDESCRIPTION_CA2C90E4_HPP
#define POMDOG_SAMPLERDESCRIPTION_CA2C90E4_HPP

#include "TextureAddressMode.hpp"
#include "TextureFilter.hpp"
#include "Pomdog/Basic/Export.hpp"
#include <cstdint>
#include <limits>

namespace Pomdog {

class POMDOG_EXPORT SamplerDescription {
public:
    std::uint32_t MaxAnisotropy = 0;

    float MinMipLevel = 0.0f;

    float MaxMipLevel = std::numeric_limits<float>::max();

    float MipMapLevelOfDetailBias = 0.0f;

    TextureFilter Filter = TextureFilter::Linear;

    TextureAddressMode AddressU = TextureAddressMode::Clamp;

    TextureAddressMode AddressV = TextureAddressMode::Clamp;

    TextureAddressMode AddressW = TextureAddressMode::Clamp;

    //Color BorderColor = Color::TransparentBlack;
};

} // namespace Pomdog

#endif // POMDOG_SAMPLERDESCRIPTION_CA2C90E4_HPP
