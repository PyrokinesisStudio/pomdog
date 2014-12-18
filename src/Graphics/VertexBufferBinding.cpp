﻿//
//  Copyright (C) 2013-2014 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#include <Pomdog/Graphics/VertexBufferBinding.hpp>
#include <utility>

namespace Pomdog {
//-----------------------------------------------------------------------
VertexBufferBinding::VertexBufferBinding(VertexDeclaration const& vertexDeclarationIn)
: Declaration(vertexDeclarationIn)
, VertexOffset(0)
, InstanceFrequency(0)
{}
//-----------------------------------------------------------------------
VertexBufferBinding::VertexBufferBinding(VertexDeclaration && vertexDeclarationIn)
: Declaration(std::move(vertexDeclarationIn))
, VertexOffset(0)
, InstanceFrequency(0)
{}
//-----------------------------------------------------------------------
VertexBufferBinding::VertexBufferBinding(VertexDeclaration const& vertexDeclarationIn,
	std::uint32_t vertexOffsetIn, std::uint32_t instanceFrequencyIn)
: Declaration(vertexDeclarationIn)
, VertexOffset(vertexOffsetIn)
, InstanceFrequency(instanceFrequencyIn)
{}
//-----------------------------------------------------------------------
VertexBufferBinding::VertexBufferBinding(VertexDeclaration && vertexDeclarationIn,
	std::uint32_t vertexOffsetIn, std::uint32_t instanceFrequencyIn)
: Declaration(std::move(vertexDeclarationIn))
, VertexOffset(vertexOffsetIn)
, InstanceFrequency(instanceFrequencyIn)
{}
//-----------------------------------------------------------------------
}// namespace Pomdog
