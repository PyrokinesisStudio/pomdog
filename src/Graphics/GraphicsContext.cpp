//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include <Pomdog/Graphics/GraphicsContext.hpp>
#include <vector>
#include <utility>
#include <Pomdog/Utility/Assert.hpp>
#include <Pomdog/Utility/Exception.hpp>
#include <Pomdog/Graphics/BlendState.hpp>
#include <Pomdog/Graphics/DepthStencilState.hpp>
#include <Pomdog/Graphics/RasterizerState.hpp>
#include <Pomdog/Graphics/SamplerState.hpp>
#include <Pomdog/Graphics/Texture2D.hpp>
#include <Pomdog/Graphics/VertexBufferBinding.hpp>
#include <Pomdog/Graphics/Viewport.hpp>
#include "../RenderSystem/GraphicsCapabilities.hpp"
#include "../RenderSystem/NativeGraphicsContext.hpp"
#include "../RenderSystem/NativeBlendState.hpp"
#include "../RenderSystem/NativeDepthStencilState.hpp"
#include "../RenderSystem/NativeRasterizerState.hpp"
#include "../RenderSystem/NativeSamplerState.hpp"
#include "../RenderSystem/NativeTexture2D.hpp"
#include "../RenderSystem/PresentationParameters.hpp"
#include "../Utility/MakeUnique.hpp"

namespace Pomdog {

using Details::PresentationParameters;

//-----------------------------------------------------------------------
#if defined(POMDOG_COMPILER_CLANG)
#pragma mark - GraphicsContext::Impl class
#endif
//-----------------------------------------------------------------------
class GraphicsContext::Impl final
{
public:
	Impl() = delete;
	Impl(Impl const&) = delete;
	Impl(Impl &&) = default;
	
	Impl(std::unique_ptr<Details::RenderSystem::NativeGraphicsContext> nativeContext,
		PresentationParameters const& presentationParameters);
	
	void BuildResources(std::shared_ptr<GraphicsDevice> const& graphicsDevice);
	
	///@copydoc GraphicsContext
	void SetViewport(Viewport const& viewport);
	
	///@copydoc GraphicsContext
	void SetSamplerState(std::uint32_t samplerSlot, std::shared_ptr<SamplerState> const& samplerState);
	
	///@copydoc GraphicsContext
	void SetTexture(std::uint32_t textureSlot);
	
	///@copydoc GraphicsContext
	void SetTexture(std::uint32_t textureSlot, std::shared_ptr<Texture2D> const& texture);
	
public:
	Viewport viewport;
	std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
	std::vector<std::shared_ptr<SamplerState>> samplerStates;
	std::vector<std::shared_ptr<Texture2D>> textures;
	std::shared_ptr<BlendState> blendState;
	std::shared_ptr<DepthStencilState> depthStencilState;
	std::shared_ptr<RasterizerState> rasterizerState;
	std::shared_ptr<InputLayout> inputLayout;
	
	std::unique_ptr<Details::RenderSystem::NativeGraphicsContext> nativeContext;
};
//-----------------------------------------------------------------------
GraphicsContext::Impl::Impl(std::unique_ptr<Details::RenderSystem::NativeGraphicsContext> nativeGraphicsContext,
	PresentationParameters const& presentationParameters)
	: nativeContext(std::move(nativeGraphicsContext))
{
	POMDOG_ASSERT(nativeContext);
	auto graphicsCapbilities = nativeContext->GetCapabilities();

	POMDOG_ASSERT(graphicsCapbilities.SamplerSlotCount > 0);
	samplerStates.clear();
	samplerStates.resize(graphicsCapbilities.SamplerSlotCount);
	textures.clear();
	textures.resize(graphicsCapbilities.SamplerSlotCount);
	
	viewport.bounds.x = 0;
	viewport.bounds.y = 0;
	viewport.Width(presentationParameters.BackBufferWidth);
	viewport.Height(presentationParameters.BackBufferHeight);
	SetViewport(viewport);
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::BuildResources(std::shared_ptr<GraphicsDevice> const& graphicsDevice)
{
	POMDOG_ASSERT(nativeContext);
	POMDOG_ASSERT(graphicsDevice);
		
	blendState = BlendState::CreateOpaque(graphicsDevice);
	rasterizerState = RasterizerState::CreateCullCounterClockwise(graphicsDevice);
	depthStencilState = DepthStencilState::CreateReadWriteDepth(graphicsDevice);
	
	POMDOG_ASSERT(!samplerStates.empty());
	for (std::size_t index = 0; index < samplerStates.size(); ++index) {
		samplerStates[index] = SamplerState::CreateLinearClamp(graphicsDevice);
	}

	if (blendState) {
		blendState->NativeBlendState()->Apply();
	}
	if (depthStencilState) {
		depthStencilState->NativeDepthStencilState()->Apply();
	}
	if (rasterizerState) {
		rasterizerState->NativeRasterizerState()->Apply();
	}
	for (std::uint32_t index = 0; index < samplerStates.size(); ++index) {
		if (samplerStates[index]) {
			samplerStates[index]->NativeSamplerState()->Apply(index);
		}
	}
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::SetViewport(Viewport const& newViewport)
{
	POMDOG_ASSERT(nativeContext);
	POMDOG_ASSERT(newViewport.Width() > 0);
	POMDOG_ASSERT(newViewport.Height() > 0);

	this->viewport = newViewport;
	nativeContext->SetViewport(this->viewport);
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::SetSamplerState(std::uint32_t samplerSlot, std::shared_ptr<SamplerState> const& samplerStateIn)
{
	POMDOG_ASSERT(samplerStateIn);
	POMDOG_ASSERT(!samplerStates.empty());
	POMDOG_ASSERT(samplerStates.size() > samplerSlot);
	
	if (samplerStates.size() > samplerSlot)
	{
		samplerStates[samplerSlot] = samplerStateIn;
	
		POMDOG_ASSERT(samplerStateIn->NativeSamplerState());
		samplerStateIn->NativeSamplerState()->Apply(samplerSlot);
	}
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::SetTexture(std::uint32_t textureSlot)
{
	POMDOG_ASSERT(!textures.empty());
	POMDOG_ASSERT(textures.size() > textureSlot);
	
	if (textures.size() > textureSlot)
	{
		if (auto texture = textures[textureSlot])
		{
			POMDOG_ASSERT(texture->NativeTexture2D());
			texture->NativeTexture2D()->UnbindFromTextureUnit(textureSlot);
		}
		textures[textureSlot].reset();
	}
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::SetTexture(std::uint32_t textureSlot, std::shared_ptr<Texture2D> const& textureIn)
{
	POMDOG_ASSERT(textureIn);
	POMDOG_ASSERT(!textures.empty());
	POMDOG_ASSERT(textures.size() > textureSlot);
	
	if (textures.size() > textureSlot)
	{
		textures[textureSlot] = textureIn;
		
		POMDOG_ASSERT(textureIn->NativeTexture2D());
		textureIn->NativeTexture2D()->Apply(textureSlot);
	}
}
//-----------------------------------------------------------------------
#if defined(POMDOG_COMPILER_CLANG)
#pragma mark - GraphicsContext class
#endif
//-----------------------------------------------------------------------
GraphicsContext::GraphicsContext(
	std::unique_ptr<Details::RenderSystem::NativeGraphicsContext> nativeContext,
	Details::PresentationParameters const& presentationParameters,
	std::shared_ptr<GraphicsDevice> const& graphicsDevice)
	: impl(Details::MakeUnique<Impl>(std::move(nativeContext), presentationParameters))
{
	POMDOG_ASSERT(graphicsDevice);
	impl->BuildResources(graphicsDevice);
}
//-----------------------------------------------------------------------
GraphicsContext::~GraphicsContext() = default;
//-----------------------------------------------------------------------
void GraphicsContext::Clear(Color const& color)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	impl->nativeContext->Clear(color);
}
//-----------------------------------------------------------------------
void GraphicsContext::Clear(ClearOptions options, Color const& color, float depth, std::int32_t stencil)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	impl->nativeContext->Clear(options, color, depth, stencil);
}
//-----------------------------------------------------------------------
void GraphicsContext::Present()
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	impl->nativeContext->Present();
}
//-----------------------------------------------------------------------
void GraphicsContext::Draw(PrimitiveTopology primitiveTopology)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->nativeContext->Draw(primitiveTopology);
}
//-----------------------------------------------------------------------
void GraphicsContext::DrawIndexed(PrimitiveTopology primitiveTopology,
	std::shared_ptr<IndexBuffer> const& indexBuffer, std::uint32_t indexCount)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->nativeContext->DrawIndexed(primitiveTopology, indexBuffer, indexCount);
}
//-----------------------------------------------------------------------
void GraphicsContext::DrawInstanced(PrimitiveTopology primitiveTopology, std::uint32_t instanceCount)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->nativeContext->DrawInstanced(primitiveTopology, instanceCount);
}
//-----------------------------------------------------------------------
void GraphicsContext::DrawIndexedInstanced(PrimitiveTopology primitiveTopology,
	std::shared_ptr<IndexBuffer> const& indexBuffer, std::uint32_t indexCount, std::uint32_t instanceCount)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->nativeContext->DrawIndexedInstanced(primitiveTopology, indexBuffer, indexCount, instanceCount);
}
//-----------------------------------------------------------------------
Viewport const& GraphicsContext::GetViewport() const
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	return impl->viewport;
}
//-----------------------------------------------------------------------
void GraphicsContext::SetViewport(Viewport const& viewport)
{
	POMDOG_ASSERT(impl);
	impl->SetViewport(viewport);
}
//-----------------------------------------------------------------------
Rectangle GraphicsContext::GetScissorRectangle() const
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	return impl->nativeContext->GetScissorRectangle();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetScissorRectangle(Pomdog::Rectangle const& rectangle)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	impl->nativeContext->SetScissorRectangle(rectangle);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetBlendState(std::shared_ptr<BlendState> const& blendState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(blendState);
	impl->blendState = blendState;
	impl->blendState->NativeBlendState()->Apply();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetDepthStencilState(std::shared_ptr<DepthStencilState> const& depthStencilState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(depthStencilState);
	impl->depthStencilState = depthStencilState;
	impl->depthStencilState->NativeDepthStencilState()->Apply();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetRasterizerState(std::shared_ptr<RasterizerState> const& rasterizerState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(rasterizerState);
	impl->rasterizerState = rasterizerState;
	impl->rasterizerState->NativeRasterizerState()->Apply();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetSamplerState(std::uint32_t index, std::shared_ptr<SamplerState> const& samplerState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(samplerState);
	impl->SetSamplerState(index, samplerState);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetInputLayout(std::shared_ptr<InputLayout> const& inputLayout)
{
	POMDOG_ASSERT(inputLayout);
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->inputLayout = inputLayout;
	impl->nativeContext->SetInputLayout(inputLayout);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetVertexBuffer(std::shared_ptr<VertexBuffer> const& vertexBuffer)
{
	POMDOG_ASSERT(vertexBuffer);
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->vertexBuffers.clear();
	impl->vertexBuffers.push_back(vertexBuffer);
	
	impl->nativeContext->SetVertexBuffers(impl->vertexBuffers);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetVertexBuffers(std::vector<std::shared_ptr<VertexBuffer>> const& vertexBuffers)
{
	POMDOG_ASSERT(vertexBuffers.empty());
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->vertexBuffers = vertexBuffers;
	impl->nativeContext->SetVertexBuffers(impl->vertexBuffers);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetTexture(std::uint32_t index)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->SetTexture(index);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetTexture(std::uint32_t index, std::shared_ptr<Texture2D> const& texture)
{
	POMDOG_ASSERT(texture);
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	
	impl->SetTexture(index, texture);
}
//-----------------------------------------------------------------------
Details::RenderSystem::NativeGraphicsContext* GraphicsContext::NativeGraphicsContext()
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	return impl->nativeContext.get();
}
//-----------------------------------------------------------------------
}// namespace Pomdog
