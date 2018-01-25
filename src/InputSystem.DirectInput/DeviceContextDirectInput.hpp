// Copyright (c) 2013-2018 mogemimi. Distributed under the MIT license.

#pragma once

#include "PrerequisitesDirectInput.hpp"
#include "../Utility/Noncopyable.hpp"
#include <wrl/client.h>
#include <memory>

namespace Pomdog {
namespace Detail {
namespace InputSystem {
namespace DirectInput {

class DeviceContextDirectInput final : Noncopyable {
public:
    DeviceContextDirectInput(HINSTANCE hInstance, HWND windowHandle);

    ~DeviceContextDirectInput();

    HWND WindowHandle() const;

    IDirectInput8* GetDirectInput() const;

private:
    HWND windowHandle;
    Microsoft::WRL::ComPtr<IDirectInput8> directInput;
};

} // namespace DirectInput
} // namespace InputSystem
} // namespace Detail
} // namespace Pomdog
