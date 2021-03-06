// Copyright (c) 2013-2018 mogemimi. Distributed under the MIT license.

#pragma once

#include "Pomdog/Graphics/detail/ForwardDeclarations.hpp"
#include "Pomdog/Utility/Optional.hpp"
#import <Metal/MTLTexture.h>

namespace Pomdog {
namespace Detail {
namespace Metal {

struct MetalFormatHelper final {
    static Optional<MTLPixelFormat> ToMTLPixelFormat(SurfaceFormat format) noexcept;
};

} // namespace Metal
} // namespace Detail
} // namespace Pomdog
