﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "MaidBeamGame.hpp"
#include <utility>
#include <Pomdog/Utility/MakeUnique.hpp>
#include "SpriteBatch.hpp"
#include "SpriteRenderer.hpp"
#include "FXAA.hpp"
#include "SandboxHelper.hpp"
#include "UI/StackPanel.hpp"
#include "UI/DebugNavigator.hpp"

#include "Skeletal2D/AnimationTrack.hpp"
#include "Skeletal2D/SkeletonHelper.hpp"
#include "Skeletal2D/SkinnedMesh.hpp"
#include "Spine/SkeletonDescLoader.hpp"
#include "Spine/AnimationLoader.hpp"
#include "Spine/SkeletonLoader.hpp"
#include "Spine/SkinLoader.hpp"
#include "Spine/SpriteAnimationLoader.hpp"
#include "Spine/SkinnedMeshLoader.hpp"
#include "TexturePacker/TextureAtlasLoader.hpp"
#include "LogSkeletalInfo.hpp"
#include "Skeletal2D/AnimationNode.hpp"
#include "Skeletal2D/AnimationAdditiveNode.hpp"
#include "Skeletal2D/AnimationLerpNode.hpp"
#include "Skeletal2D/AnimationClipNode.hpp"
#include "Graphics/SpriteLine.hpp"


namespace TestApp {
//-----------------------------------------------------------------------
MaidBeamGame::MaidBeamGame(std::shared_ptr<GameHost> const& gameHostIn)
	: gameHost(gameHostIn)
{
	POMDOG_ASSERT(gameHostIn);
	graphicsContext = gameHost->GraphicsContext();
}
//-----------------------------------------------------------------------
MaidBeamGame::~MaidBeamGame() = default;
//-----------------------------------------------------------------------
void MaidBeamGame::Initialize()
{
	auto window = gameHost->Window();
	window->Title("TestApp - Enjoy Game Dev, Have Fun.");
	window->AllowPlayerResizing(true);
	
	auto graphicsDevice = gameHost->GraphicsDevice();
	auto assets = gameHost->AssetManager();

	{
		samplerPoint = SamplerState::CreateLinearWrap(graphicsDevice);
		
		auto blendState = BlendState::CreateNonPremultiplied(graphicsDevice);
		graphicsContext->SetBlendState(blendState);
		texture = assets->Load<Texture2D>("pomdog.png");
	}
	{
		renderTarget = std::make_shared<RenderTarget2D>(graphicsDevice,
			window->ClientBounds().Width, window->ClientBounds().Height,
			false, SurfaceFormat::R8G8B8A8_UNorm, DepthFormat::None);
	}
	{
		spriteRenderer = MakeUnique<SpriteRenderer>(graphicsContext, graphicsDevice, *assets);		
		fxaa = MakeUnique<FXAA>(gameHost);
		polygonBatch = MakeUnique<PolygonBatch>(graphicsContext, graphicsDevice, *assets);
	}
	{
		gameEditor = MakeUnique<SceneEditor::InGameEditor>(gameHost);
	}
	
	rootNode = std::make_shared<HierarchyNode>();
	{
		auto gameObject = gameWorld.CreateObject();
		mainCamera = gameObject;

		gameObject->AddComponent<Transform2D>();
		gameObject->AddComponent<CanvasItem>();
		gameObject->AddComponent<Camera2D>();

		auto node = std::make_shared<HierarchyNode>(gameObject);
		rootNode->AddChild(node);
	}
	{
		auto textureAtlas = assets->Load<Details::TexturePacker::TextureAtlas>("MaidGun/MaidGun.atlas");
		auto skeletonDesc = assets->Load<Details::Skeletal2D::SkeletonDesc>("MaidGun/MaidGun.json");
		maidTexture = assets->Load<Texture2D>("MaidGun/MaidGun.png");
		
		LogSkeletalInfo(textureAtlas, skeletonDesc);
		
		maidSkeleton = std::make_shared<Skeleton>(Details::Skeletal2D::CreateSkeleton(skeletonDesc.Bones));
		maidSkeletonPose = std::make_shared<SkeletonPose>(SkeletonPose::CreateBindPose(*maidSkeleton));
		auto animationClip = std::make_shared<AnimationClip>(Details::Skeletal2D::CreateAnimationClip(skeletonDesc, "Run"));
		maidAnimationState = std::make_shared<AnimationState>(animationClip, 1.0f, true);
		maidAnimationClipIdle = std::make_shared<AnimationClip>(Details::Skeletal2D::CreateAnimationClip(skeletonDesc, "RunNoShot"));
		
		maidSkin = Details::Skeletal2D::CreateSkin(skeletonDesc, textureAtlas, "default");
		maidSpriteAnimationTracks = Details::Skeletal2D::CreateSpriteAnimationTrack(skeletonDesc, textureAtlas, "Run");
		
		animationSystem.Add(maidAnimationState, maidSkeleton, maidSkeletonPose);

		maidGlobalPose = SkeletonHelper::ToGlobalPose(*maidSkeleton, *maidSkeletonPose);

		// NOTE: for Skinning
		auto bindPose = SkeletonPose::CreateBindPose(*maidSkeleton);
		maidSkinnedMesh = Details::Skeletal2D::CreateSkinnedMesh(graphicsDevice,
			SkeletonHelper::ToGlobalPose(*maidSkeleton, bindPose),
			skeletonDesc, textureAtlas,
			Vector2(maidTexture->Width(), maidTexture->Height()), "default");
		maidSkinningEffect = assets->Load<EffectPass>("Effects/SkinningSpriteEffect");
		maidInputLayout = std::make_shared<InputLayout>(graphicsDevice, maidSkinningEffect);
	}
	{
		beamTexture = assets->Load<Texture2D>("Particles/lightning.png");
	}
	
	{
		scenePanel = std::make_shared<UI::ScenePanel>(window->ClientBounds().Width, window->ClientBounds().Height);
		scenePanel->cameraObject = mainCamera;
		gameEditor->AddView(scenePanel);
	}
	{
		auto stackPanel = std::make_shared<UI::StackPanel>(124, 170);
		stackPanel->Transform(Matrix3x2::CreateTranslation(Vector2{5, 10}));
		gameEditor->AddView(stackPanel);

		{
			auto navigator = std::make_shared<UI::DebugNavigator>(gameHost->Clock());
			stackPanel->AddChild(navigator);
		}
		{
			slider1 = std::make_shared<UI::Slider>(0.3, 1.48);
			slider1->Value(1.48);
			stackPanel->AddChild(slider1);
		}
		{
			slider2 = std::make_shared<UI::Slider>(0.0, 1.0);
			slider2->Value(1.0);
			stackPanel->AddChild(slider2);
		}
		{
			toggleSwitch1 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch1->IsOn(true);
			toggleSwitch1->OnContent("Play");
			toggleSwitch1->OffContent("Stop");
			stackPanel->AddChild(toggleSwitch1);
		}
		{
			toggleSwitch2 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch2->IsOn(true);
			stackPanel->AddChild(toggleSwitch2);
		}
		{
			toggleSwitch3 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch3->IsOn(false);
			stackPanel->AddChild(toggleSwitch3);
		}
		{
			toggleSwitch4 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch4->IsOn(false);
			stackPanel->AddChild(toggleSwitch4);
		}
	}
	
	clientSizeChangedConnection = window->ClientSizeChanged.Connect([this] {
		auto gameWindow = gameHost->Window();
		auto bounds = gameWindow->ClientBounds();
		
		renderTarget = std::make_shared<RenderTarget2D>(
			gameHost->GraphicsDevice(), bounds.Width, bounds.Height,
			false, SurfaceFormat::R8G8B8A8_UNorm, DepthFormat::None);

		fxaa->ResetViewportSize(bounds);
		spriteRenderer->SetProjectionMatrix(Matrix4x4::CreateOrthographicLH(bounds.Width, bounds.Height, 1.0f, 100.0f));
	});
}
//-----------------------------------------------------------------------
void MaidBeamGame::Update()
{
	auto clock = gameHost->Clock();
	auto mouse = gameHost->Mouse();
	{
		gameEditor->Update();
	}
	{
		maidAnimationState->PlaybackRate(slider1->Value());
	}
	
	if (toggleSwitch1->IsOn())
	{
		animationSystem.Update(*clock);
		
		SkeletonHelper::ToGlobalPose(*maidSkeleton, *maidSkeletonPose, maidGlobalPose);
	
		{
			///@note Test code for animation blending
			auto clipNode1 = MakeUnique<AnimationClipNode>(maidAnimationState->Clip());
			auto clipNode2 = MakeUnique<AnimationClipNode>(maidAnimationClipIdle);
		
			auto lerpNode = MakeUnique<AnimationLerpNode>(std::move(clipNode1), std::move(clipNode2));
			lerpNode->Weight(slider2->Value());
			
			lerpNode->Calculate(maidAnimationState->Time(), *maidSkeleton, *maidSkeletonPose);
			
			SkeletonHelper::ToGlobalPose(*maidSkeleton, *maidSkeletonPose, maidGlobalPose);
		}
	}
	{
		maidAnimationTimer.Update(clock->FrameDuration());
		if (maidAnimationTimer.Time() > maidAnimationState->Length()) {
			maidAnimationTimer.Reset();
		}
	}
	{
		for (auto & track: maidSpriteAnimationTracks)
		{
			track.Apply(maidSkin, maidAnimationTimer.Time());
		}
	}
	{
		beamSystem.emitter.InterpolationPoints = static_cast<std::uint16_t>(95);
		beamSystem.emitter.StartThickness = 1.374f;
		beamSystem.branching.BranchingRate = 0.134f;
		beamSystem.branching.InheritThickness = 0.5f;
		beamSystem.emitter.SwayRange = std::uniform_real_distribution<float>(-12.5f, 12.5f);
		beamSystem.branching.SpreadRange = std::uniform_real_distribution<float>(-2.357f, 2.357f);
		beamSystem.emitter.EndColor = Color{102,122,204,255};
		beamSystem.emitter.StartLifetime = 0.4f;
	}
	{
		//auto const& muzzleRifleMatrix = maidGlobalPose[35];
		auto const& muzzleRifleMatrix = Matrix3x2::Identity;
	
		Transform2D transform;
		transform.Scale = {1.0f, 1.0f};
		transform.Rotation = 0.0f;
		transform.Position = Vector2::Transform(Vector2{10.0f, 0.0f}, muzzleRifleMatrix);
		Vector2 target = Vector2::Transform(Vector2{500.0f, 0.0f}, muzzleRifleMatrix);
		
		if (slider2->Value() > 0.4f) {
			transform.Position = {900.0f, 1000.0f};
			target = transform.Position + Vector2{100.0f, 100.0f};
		}
		
		beamSystem.Update(clock->FrameDuration(), transform, target);
	}
}
//-----------------------------------------------------------------------
void MaidBeamGame::DrawSprites()
{
	auto transform = mainCamera->Component<Transform2D>();
	auto camera = mainCamera->Component<Camera2D>();
		
	POMDOG_ASSERT(transform && camera);
	auto viewMatrix = SandboxHelper::CreateViewMatrix(*transform, *camera);;
	auto projectionMatrix = Matrix4x4::CreateOrthographicLH(
		gameHost->Window()->ClientBounds().Width, gameHost->Window()->ClientBounds().Height, 0.1f, 1000.0f);

	POMDOG_ASSERT(polygonBatch);
	polygonBatch->Begin(viewMatrix * projectionMatrix);

	auto const& globalPoses = maidGlobalPose;
	
	if (toggleSwitch3->IsOn())
	{
		Color boneColor {160, 160, 160, 255};
	
		for (auto & joint: *maidSkeleton)
		{
			auto & matrix = globalPoses[*joint.Index];

			if (maidSkeleton->Root().Index != joint.Index)
			{
				polygonBatch->DrawTriangle(
					Vector2::Transform({1.7f, -4.7f}, matrix),
					Vector2::Transform({1.7f, 4.7f}, matrix),
					Vector2::Transform({25, 0}, matrix), boneColor);
			}
			
			auto center = Vector2::Transform(Vector2::Zero, matrix);
			polygonBatch->DrawCircle(center, 5.0f, boneColor, 18);
			polygonBatch->DrawCircle(center, 3.0f, Color::White, 13);
		}
	}
	
	polygonBatch->End();
}
//-----------------------------------------------------------------------
void MaidBeamGame::DrawSkinnedMesh()
{
	{
		auto transform = mainCamera->Component<Transform2D>();
		auto camera = mainCamera->Component<Camera2D>();
		
		POMDOG_ASSERT(transform && camera);
		auto viewMatrix = SandboxHelper::CreateViewMatrix(*transform, *camera);;
		auto projectionMatrix = Matrix4x4::CreateOrthographicLH(
			graphicsContext->Viewport().Width(), graphicsContext->Viewport().Height(), 0.1f, 1000.0f);
		
		maidSkinningEffect->Parameters("Constants")->SetValue(Matrix4x4::Transpose(viewMatrix * projectionMatrix));

		struct MatrixPalette {
			std::array<Vector4, 64> matrixPalette1;
			std::array<Vector4, 64> matrixPalette2;
		};
		MatrixPalette matrixPalette;
		
		std::array<Matrix3x2, 64> matrices;

		for (auto & joint: *maidSkeleton)
		{
			POMDOG_ASSERT(joint.Index);
			POMDOG_ASSERT(*joint.Index < matrices.size());
			POMDOG_ASSERT(*joint.Index < maidGlobalPose.size());
			matrices[*joint.Index] = joint.InverseBindPose * maidGlobalPose[*joint.Index];
		}

		for (std::size_t i = 0; i < matrices.size(); ++i) {
			matrixPalette.matrixPalette1[i].X = matrices[i](0, 0);
			matrixPalette.matrixPalette1[i].Y = matrices[i](0, 1);
			matrixPalette.matrixPalette1[i].Z = matrices[i](1, 0);
			matrixPalette.matrixPalette1[i].W = matrices[i](1, 1);
			matrixPalette.matrixPalette2[i].X = matrices[i](2, 0);
			matrixPalette.matrixPalette2[i].Y = matrices[i](2, 1);
		}

		maidSkinningEffect->Parameters("SkinningConstants")->SetValue(matrixPalette);
	}
	
	if (toggleSwitch2->IsOn())
	{
		graphicsContext->SetTexture(0, maidTexture);
		graphicsContext->SetInputLayout(maidInputLayout);
		graphicsContext->SetVertexBuffer(maidSkinnedMesh.VertexBuffer);
		maidSkinningEffect->Apply();
		graphicsContext->DrawIndexed(PrimitiveTopology::TriangleList,
			maidSkinnedMesh.IndexBuffer, maidSkinnedMesh.IndexBuffer->IndexCount());
	}
	
	if (toggleSwitch4->IsOn())
	{
		RasterizerDescription rasterizerDesc;
		rasterizerDesc.FillMode = FillMode::WireFrame;
		auto rasterizerState = std::make_shared<RasterizerState>(gameHost->GraphicsDevice(), rasterizerDesc);
		
		graphicsContext->SetRasterizerState(rasterizerState);
		
		graphicsContext->SetTexture(0, texture);
		graphicsContext->SetInputLayout(maidInputLayout);
		graphicsContext->SetVertexBuffer(maidSkinnedMesh.VertexBuffer);
		maidSkinningEffect->Apply();
		graphicsContext->DrawIndexed(PrimitiveTopology::TriangleList,
									 maidSkinnedMesh.IndexBuffer, maidSkinnedMesh.IndexBuffer->IndexCount());
		
		
		graphicsContext->SetRasterizerState(RasterizerState::CreateCullCounterClockwise(gameHost->GraphicsDevice()));
	}
}
//-----------------------------------------------------------------------
void MaidBeamGame::DrawBeam()
{
	auto transform = mainCamera->Component<Transform2D>();
	auto camera = mainCamera->Component<Camera2D>();

	POMDOG_ASSERT(transform && camera);
	auto viewMatrix = SandboxHelper::CreateViewMatrix(*transform, *camera);
	auto projectionMatrix = Matrix4x4::CreateOrthographicLH(
		graphicsContext->Viewport().Width(), graphicsContext->Viewport().Height(), 0.1f, 1000.0f);

	gameEditor->SetViewProjection(viewMatrix * projectionMatrix);

	auto const& muzzleRifleMatrix = maidGlobalPose[35];
	auto transposeMatrix = Matrix4x4{
		muzzleRifleMatrix(0, 0), muzzleRifleMatrix(0, 1), 0.0f, 0.0f,
		muzzleRifleMatrix(1, 0), muzzleRifleMatrix(1, 1), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		muzzleRifleMatrix(2, 0), muzzleRifleMatrix(2, 1), 0.0f, 1.0f,
	};

	POMDOG_ASSERT(spriteRenderer);
	spriteRenderer->Begin(SpriteSortMode::Deferred, transposeMatrix * viewMatrix);
	{
		SpriteLine spriteLine;
		spriteLine.Texture = beamTexture;
		spriteLine.HalfCircleSize = {8, 32};
		spriteLine.InverseThickness = 5.0f;
		spriteLine.StartRectangle = {0, 0, 32, 64};
		spriteLine.MiddleRectangle = {32, 0, 1, 64};
		spriteLine.EndRectangle = {33, 0, 31, 64};

		auto DrawBeam = [&](std::vector<Vector2> const& points, float lineThickness, Color const& color, float normalizedTime)
		{
			if (normalizedTime > 0.2f) {
				for (std::size_t i = 1; i < points.size(); ++i)
				{
					POMDOG_ASSERT(i > 0);
					auto & start = points[i - 1];
					auto & end = points[i];
					
					spriteLine.Draw(*spriteRenderer, start, end, lineThickness, color, 0);
				}
			}
			else {
				auto a = points.size() - static_cast<std::size_t>(std::max(1.0f, normalizedTime * (points.size() - 1)));
				POMDOG_ASSERT(a < points.size());
				for (std::size_t i = a; i < points.size(); ++i)
				{
					POMDOG_ASSERT(i > 0);
					auto & start = points[i - 1];
					auto & end = points[i];
					
					spriteLine.Draw(*spriteRenderer, start, end, lineThickness, color, 0);
				}
			}
		};
		
		for (auto & beam: beamSystem.beams)
		{
			DrawBeam(beam.Points, beam.Thickness, beam.Color, beam.TimeToLive/beamSystem.emitter.StartLifetime);
		}
	}
	spriteRenderer->End();
}
//-----------------------------------------------------------------------
void MaidBeamGame::Draw()
{
	constexpr bool enableFxaa = true;

	if (enableFxaa) {
		graphicsContext->SetRenderTarget(renderTarget);
	}
	
	graphicsContext->Clear(Color::CornflowerBlue);
	{
		auto transform = mainCamera->Component<Transform2D>();
		auto camera = mainCamera->Component<Camera2D>();
			
		POMDOG_ASSERT(transform && camera);
		auto viewMatrix = SandboxHelper::CreateViewMatrix(*transform, *camera);;
		auto projectionMatrix = Matrix4x4::CreateOrthographicLH(
			graphicsContext->Viewport().Width(), graphicsContext->Viewport().Height(), 0.1f, 1000.0f);
		
		gameEditor->SetViewProjection(viewMatrix * projectionMatrix);
	}
	gameEditor->BeginDraw(*graphicsContext);

	graphicsContext->SetSamplerState(0, samplerPoint);
	DrawSprites();
	DrawSkinnedMesh();
	
	auto blendStateAdditive = BlendState::CreateAdditive(gameHost->GraphicsDevice());
	auto blendState = graphicsContext->GetBlendState();
	graphicsContext->SetBlendState(blendStateAdditive);
	DrawBeam();
	graphicsContext->SetBlendState(blendState);
	
	if (enableFxaa) {
		graphicsContext->SetRenderTarget();
		fxaa->Draw(*graphicsContext, renderTarget);
	}

	gameEditor->EndDraw(*graphicsContext);
	graphicsContext->Present();
}
//-----------------------------------------------------------------------
}// namespace TestApp
