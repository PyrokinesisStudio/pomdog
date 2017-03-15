// Copyright (c) 2013-2017 mogemimi. Distributed under the MIT license.

#pragma once

#include "Pomdog/Graphics/detail/ForwardDeclarations.hpp"
#include "Pomdog/Basic/Export.hpp"
#include <memory>

namespace Pomdog {

class POMDOG_EXPORT GraphicsDevice final {
public:
    GraphicsDevice() = delete;
    GraphicsDevice(const GraphicsDevice&) = delete;
    GraphicsDevice & operator=(const GraphicsDevice&) = delete;

    explicit GraphicsDevice(std::unique_ptr<Detail::NativeGraphicsDevice> && nativeDevice);

    ~GraphicsDevice();

    ShaderLanguage GetSupportedLanguage() const;

    Detail::NativeGraphicsDevice* GetNativeGraphicsDevice();

private:
    std::unique_ptr<Detail::NativeGraphicsDevice> nativeGraphicsDevice;
};

} // namespace Pomdog
