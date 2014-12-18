﻿//
//  Copyright (C) 2013-2014 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_RASTERIZERDESCRIPTION_AD753EE4_3D3A_44B2_85B3_A54B2C5D1B4A_HPP
#define POMDOG_RASTERIZERDESCRIPTION_AD753EE4_3D3A_44B2_85B3_A54B2C5D1B4A_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

#include "CullMode.hpp"
#include "FillMode.hpp"
#include "Pomdog/Config/Export.hpp"
#include <cstdint>

namespace Pomdog {

///@~Japanese
/// @brief ラスタライズ処理を記述します。
class POMDOG_EXPORT RasterizerDescription {
public:
	///@~Japanese
	/// @brief 深度テストの時にピクセルに加算される深度バイアスです。デフォルト値は 0 です。
	std::int32_t DepthBias = 0;
	
	///@~Japanese
	/// @note 深度バイアスに掛ける係数です。デフォルト値は 0 です。
	float SlopeScaledDepthBias = 0;

	///@~Japanese
	/// @brief カリングモードを指定します。デフォルト値は CullMode::CounterClockwiseFace です。
	CullMode CullMode = CullMode::CounterClockwiseFace;

	///@~Japanese
	/// @brief 三角形の塗りつぶし方法を指定します。デフォルト値は FillMode::Solid です。
	FillMode FillMode = FillMode::Solid;
	
	///@~Japanese
	/// @brief マルチサンプリングのアンチエイリアシングが有効かどうか指定します。デフォルト値は無効 (false) です。
	/// @remarks アンチエイリアシングが有効な場合は true を、無効な場合は false を指定します。
	bool MultisampleEnable = false;
	
	///@~Japanese
	/// @brief シザーテストが有効かどうかを指定します。デフォルト値は無効 (false) です。
	/// @remarks シザーテストが有効な場合は true を、無効な場合は false を指定します。
	/// @note シザー矩形は GraphicsContext::SetScissorRectangle で指定します。
	bool ScissorTestEnable = false;
};

}// namespace Pomdog

#endif // !defined(POMDOG_RASTERIZERDESCRIPTION_AD753EE4_3D3A_44B2_85B3_A54B2C5D1B4A_HPP)
