﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_NATIVEDEPTHSTENCILSTATE_A8D5CCF3_A7B5_401E_970A_65DF722150AB_HPP
#define POMDOG_NATIVEDEPTHSTENCILSTATE_A8D5CCF3_A7B5_401E_970A_65DF722150AB_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

namespace Pomdog {
namespace Details {
namespace RenderSystem {

class NativeGraphicsContext;

class NativeDepthStencilState {
public:
	NativeDepthStencilState() = default;
	NativeDepthStencilState(NativeDepthStencilState const&) = delete;
	NativeDepthStencilState & operator=(NativeDepthStencilState const&) = delete;

	virtual ~NativeDepthStencilState() = default;
	
	///@~Japanese
	/// @brief レンダリングの直前に深度ステンシルステートを適用します。
	virtual void Apply(NativeGraphicsContext & graphicsContext) = 0;
};

}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_NATIVEDEPTHSTENCILSTATE_A8D5CCF3_A7B5_401E_970A_65DF722150AB_HPP)
