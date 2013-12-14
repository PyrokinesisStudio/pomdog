//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_BUTTONSTATE_092E7B2B_0243_46C2_B46E_43B330ED0F44_HPP
#define POMDOG_BUTTONSTATE_092E7B2B_0243_46C2_B46E_43B330ED0F44_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "../Config/FundamentalTypes.hpp"

namespace Pomdog {

/// @addtogroup Framework
/// @{
/// @addtogroup Input
/// @{

///@~Japanese
/// @brief ボタンが押されているかどうかの状態を表す列挙体です。
enum class ButtonState: std::uint8_t
{
	///@~Japanese
	/// @brief ボタンが離されている状態を表します。
	Released,

	///@~Japanese
	/// @brief ボタンが押されている状態を表します。
	Pressed
};

/// @}
/// @}

}// namespace Pomdog

#endif // !defined(POMDOG_BUTTONSTATE_092E7B2B_0243_46C2_B46E_43B330ED0F44_HPP)