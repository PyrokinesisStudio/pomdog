//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_GAMEHOST_FDAA974D_DBD8_44E8_84CD_F6FAA243957B_HPP
#define POMDOG_GAMEHOST_FDAA974D_DBD8_44E8_84CD_F6FAA243957B_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <memory>
#include "../Config/Export.hpp"
#include "../Utility/Noncopyable.hpp"

namespace Pomdog {

class AssetManager;
class Game;
class GameClock;
class GameWindow;
class GraphicsContext;
class GraphicsDevice;
class Keyboard;
class Mouse;

/// @addtogroup Framework
/// @{
/// @addtogroup Application
/// @{

class POMDOG_EXPORT GameHost: Noncopyable, public std::enable_shared_from_this<GameHost> {
public:
	virtual ~GameHost() = default;
	
	///@~Japanese
	/// @brief アプリケーションを実行します。
	virtual void Run(std::weak_ptr<Game> game) = 0;
	
	///@~Japanese
	/// @brief 実行中のゲームおよびアプリケーションを終了します。
	virtual void Exit() = 0;
	
	///@~Japanese
	/// @brief ウィンドウを取得します。
	virtual std::shared_ptr<GameWindow> Window() = 0;
	
	///@~Japanese
	/// @brief ゲームクロックを取得します。
	virtual std::shared_ptr<GameClock> Clock() = 0;
	
	///@~Japanese
	/// @brief グラフィックスコンテキストを取得します。
	virtual std::shared_ptr<GraphicsContext> GraphicsContext() = 0;
	
	///@~Japanese
	/// @brief グラフィックスデバイスを取得します。
	virtual std::shared_ptr<GraphicsDevice> GraphicsDevice() = 0;
	
	///@~Japanese
	/// @brief アセットマネージャを取得します。
	virtual std::shared_ptr<AssetManager> AssetManager() = 0;
	
	///@~Japanese
	/// @brief キーボードを取得します。
	virtual std::shared_ptr<Keyboard> Keyboard() = 0;
	
	///@~Japanese
	/// @brief マウスを取得します。
	virtual std::shared_ptr<Mouse> Mouse() = 0;
};

/// @}
/// @}

}// namespace Pomdog

#endif // !defined(POMDOG_GAMEHOST_FDAA974D_DBD8_44E8_84CD_F6FAA243957B_HPP)
