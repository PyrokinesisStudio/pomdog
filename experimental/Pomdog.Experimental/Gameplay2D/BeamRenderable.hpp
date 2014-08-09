//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_BEAMRENDERABLE_5F289224_7B9B_4C29_9890_16140FFB6DFB_HPP
#define POMDOG_BEAMRENDERABLE_5F289224_7B9B_4C29_9890_16140FFB6DFB_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "Renderable.hpp"
#include <Pomdog.Experimental/Particle2D/BeamSystem.hpp>
#include <Pomdog/Pomdog.hpp>
#include <memory>

namespace Pomdog {

class BeamRenderable: public Renderable {
public:
	BeamRenderable();

	void Visit(GameObject & gameObject, Renderer & renderer, Matrix4x4 const& viewMatrix, Matrix4x4 const& projectionMatrix) override;
	
	void Load(std::shared_ptr<GraphicsDevice> const& graphicsDevice, std::shared_ptr<AssetManager> const& assets);
	void Update(GameClock const& clock);
	
	void DrawBeam();
	
private:
	BeamSystem beamSystem;
	std::shared_ptr<Texture2D> texture;
};

}// namespace Pomdog

#endif // !defined(POMDOG_BEAMRENDERABLE_5F289224_7B9B_4C29_9890_16140FFB6DFB_HPP)