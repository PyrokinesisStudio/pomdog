﻿//
//  Copyright (C) 2013-2014 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#ifndef POMDOG_LOGENTRY_F0B169C2_B3E2_4144_939B_F1FBE89BF3AC_HPP
#define POMDOG_LOGENTRY_F0B169C2_B3E2_4144_939B_F1FBE89BF3AC_HPP

#if (_MSC_VER > 1000)
#pragma once
#endif

#include "LogLevel.hpp"
#include <string>

namespace Pomdog {

///@~Japanese
/// @brief メッセージ情報を含むログエントリです。
class LogEntry {
public:
	///@~Japanese
	/// @brief ログのメッセージ本文です。
	std::string Message;
	
	///@~Japanese
	/// @brief タグです。
	std::string Tag;
	
	///@~Japanese
	/// @brief ログの冗長レベルです。
	LogLevel Verbosity;
};

}// namespace Pomdog

#endif // !defined(POMDOG_LOGENTRY_F0B169C2_B3E2_4144_939B_F1FBE89BF3AC_HPP)
