﻿//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_SRC_RENDERSYSTEM_NATIVEBLENDSTATE_95C63681_C78E_45C7_AB01_365CD02D1E06_HPP
#define POMDOG_SRC_RENDERSYSTEM_NATIVEBLENDSTATE_95C63681_C78E_45C7_AB01_365CD02D1E06_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

namespace Pomdog {
namespace Details {
namespace RenderSystem {

class NativeBlendState
{
public:
	NativeBlendState() = default;
	NativeBlendState(NativeBlendState const&) = delete;
	NativeBlendState& operator=(NativeBlendState const&) = delete;

	virtual ~NativeBlendState() = default;
	
	///@~Japanese
	/// @brief レンダリングの直前にブレンディングステートを適用します。
	virtual void Apply() = 0;
};

}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_SRC_RENDERSYSTEM_NATIVEBLENDSTATE_95C63681_C78E_45C7_AB01_365CD02D1E06_HPP)