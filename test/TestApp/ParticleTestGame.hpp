//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_PARTICLETESTGAME_CB0334A7_637D_4E14_942A_86D6617BFF5D_HPP
#define POMDOG_PARTICLETESTGAME_CB0334A7_637D_4E14_942A_86D6617BFF5D_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <Pomdog/Pomdog.hpp>
#include "SceneEditor/InGameEditor.hpp"
#include "UI/DrawingContext.hpp"
#include "UI/UIElementHierarchy.hpp"
#include "UI/ScenePanel.hpp"
#include "UI/Slider.hpp"
#include "ParticleSystem.hpp"
#include "Rendering/Renderer.hpp"

namespace TestApp {

using namespace Pomdog;

class FXAA;

class ParticleTestGame: public Game {
public:
	explicit ParticleTestGame(std::shared_ptr<GameHost> const& gameHost);

	~ParticleTestGame();

	void Initialize();
	
	void Update();
	
	void Draw();

private:
	std::shared_ptr<GameHost> gameHost;
	std::shared_ptr<GraphicsContext> graphicsContext;

	std::unique_ptr<SceneEditor::InGameEditor> gameEditor;
	std::shared_ptr<UI::ScenePanel> scenePanel;
	std::shared_ptr<UI::Slider> slider1;
	std::shared_ptr<UI::Slider> slider2;
	
	GameWorld gameWorld;
	GameObject mainCamera;
	GameObject particleObject;
	
	std::unique_ptr<Renderer> renderer;
	std::shared_ptr<RenderTarget2D> renderTarget;
	std::unique_ptr<FXAA> fxaa;
	
	ScopedConnection sceneTouchConnection;
	Vector2 touchPoint;
};

}// namespace TestApp

#endif // !defined(POMDOG_PARTICLETESTGAME_CB0334A7_637D_4E14_942A_86D6617BFF5D_HPP)
