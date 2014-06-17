//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_STACKPANEL_1285AAF5_DFD5_44B2_974C_040829A6EB6C_HPP
#define POMDOG_STACKPANEL_1285AAF5_DFD5_44B2_974C_040829A6EB6C_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <list>
#include <Pomdog/Pomdog.hpp>
#include <Pomdog/Utility/Optional.hpp>
#include "Panel.hpp"
#include "Thickness.hpp"

namespace Pomdog {
namespace UI {

class StackPanel: public Panel, public std::enable_shared_from_this<StackPanel> {
public:
	StackPanel(std::uint32_t widthIn, std::uint32_t heightIn);
	
	bool SizeToFitContent() const override { return false; }

	void OnPointerCanceled(PointerPoint const& pointerPoint) override;
	
	void OnPointerCaptureLost(PointerPoint const& pointerPoint) override;
	
	void OnPointerWheelChanged(PointerPoint const& pointerPoint) override;
	
	void OnPointerEntered(PointerPoint const& pointerPoint) override;
	
	void OnPointerExited(PointerPoint const& pointerPoint) override;
	
	void OnPointerPressed(PointerPoint const& pointerPoint) override;
	
	void OnPointerMoved(PointerPoint const& pointerPoint) override;
	
	void OnPointerReleased(PointerPoint const& pointerPoint) override;
	
	void OnRenderSizeChanged(std::uint32_t width, std::uint32_t height) override;
	
	void Draw(DrawingContext & drawingContext) override;
	
	void UpdateAnimation(DurationSeconds const& frameDuration) override;

	void AddChild(std::shared_ptr<UIView> const& element);

private:
	using UIElementCollection = std::list<std::shared_ptr<UIElement>>;
	UIElementCollection children;
	
	Thickness padding;
	std::uint16_t barHeight;
	
	Optional<Vector2> startTouchPoint;
};

}// namespace UI
}// namespace Pomdog

#endif // !defined(POMDOG_STACKPANEL_1285AAF5_DFD5_44B2_974C_040829A6EB6C_HPP)