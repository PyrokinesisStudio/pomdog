//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "GrassBlendingGame.hpp"
#include <utility>
#include <Pomdog/Utility/MakeUnique.hpp>
#include "SpriteBatch.hpp"
#include "SpriteRenderer.hpp"
#include "FXAA.hpp"
#include "SandboxHelper.hpp"
#include "UI/StackPanel.hpp"
#include "UI/DebugNavigator.hpp"

#include "TextureAtlasLoader.hpp"
#include "Skeletal2D/SkeletonDescLoader.hpp"
#include "Skeletal2D/AnimationTrack.hpp"
#include "Skeletal2D/AnimationLoader.hpp"
#include "Skeletal2D/SkeletonLoader.hpp"
#include "Skeletal2D/SkinLoader.hpp"
#include "Skeletal2D/SpriteAnimationLoader.hpp"
#include "Skeletal2D/SkeletonHelper.hpp"

namespace TestApp {
namespace {
//-----------------------------------------------------------------------
static SkeletonPose CreateSkeletonPoseBySkeleton(Skeleton const& skeleton)
{
	SkeletonPose skeletonPose;
	skeletonPose.LocalPose.reserve(skeleton.JointCount());
	for (auto & joint: skeleton) {
		skeletonPose.LocalPose.push_back(joint.BindPose);
	}

	skeletonPose.GlobalPose.resize(skeleton.JointCount());
	SkeletonHelper::ComputeGlobalPoseFromLocalPose(skeleton, skeletonPose);
	
	return std::move(skeletonPose);
}
//-----------------------------------------------------------------------
static void LogSkeletalInfo(Details::TexturePacker::TextureAtlas const& textureAtlas,
	Details::Skeletal2D::SkeletonDesc const& skeletonDesc)
{
	Log::Info(StringFormat("TextureAtlas.Pages = %ld", textureAtlas.pages.size()));
	Log::Info(StringFormat("TextureAtlas.Regions = %ld", textureAtlas.regions.size()));
	
	for (auto page: textureAtlas.pages)
	{
		Log::Info(StringFormat("Page.Name = %s", page.Name.c_str()));
	}
	
	for (auto region: textureAtlas.regions)
	{
		Log::Info(StringFormat("Region.Name = %s", region.Name.c_str()));
		Log::Info(StringFormat("  Region.Page = %d", region.TexturePage));
		Log::Info(StringFormat("  Region.Rotate = %d", region.Region.Rotate?1:0));
		Log::Info(StringFormat("  Region.Flip = %d", region.Region.Flip?1:0));
		Log::Info(StringFormat("  Region.XY = %d, %d", (int)region.Region.Subrect.X, (int)region.Region.Subrect.Y));
		Log::Info(StringFormat("  Region.Size = %d, %d", (int)region.Region.Subrect.Width, (int)region.Region.Subrect.Height));
		Log::Info(StringFormat("  Region.Offset = %d %d", (int)region.Region.XOffset, (int)region.Region.YOffset));
		Log::Info(StringFormat("  Region.OriginalSize = %d %d", (int)region.Region.Width, (int)region.Region.Height));
	}

	Log::Info("-------------------------");
	for (auto & bone: skeletonDesc.Bones)
	{
		Log::Info(StringFormat("MaidChan/%s", bone.Name.c_str()));
		Log::Info(StringFormat("  Bone.Translate = %f, %f", bone.Pose.Translate.X, bone.Pose.Translate.Y));
		Log::Info(StringFormat("  Bone.Rotation = %f", bone.Pose.Rotation.value));
		Log::Info(StringFormat("  Bone.Scale = %f", bone.Pose.Scale));
	}
	
	Log::Info("-------------------------");
	for (auto & animationClip: skeletonDesc.AnimationClips)
	{
		for (auto & track: animationClip.BoneTracks)
		{
			Log::Info(StringFormat("AnimationClip/%s/Bones/%s", animationClip.Name.c_str(), track.BoneName.c_str()));
			for (auto & sample: track.TranslateSamples)
			{
				Log::Info(StringFormat("  {time: %f, x: %f, y: %f},",
					sample.TimeSeconds,
					sample.TranslateX.ToFloat(),
					sample.TranslateY.ToFloat()));
			}
			for (auto & sample: track.RotateSamples)
			{
				Log::Info(StringFormat("  {time: %f, rotate: %f},",
					sample.TimeSeconds,
					sample.Rotation.ToFloat()));
			}
			for (auto & sample: track.ScaleSamples)
			{
				Log::Info(StringFormat("  {time: %f, rotate: %f},",
					sample.TimeSeconds,
					sample.Scale.ToFloat()));
			}
		}
		for (auto & track: animationClip.SlotTracks)
		{
			Log::Info(StringFormat("AnimationClip/%s/Slots/%s", animationClip.Name.c_str(), track.SlotName.c_str()));
			for (auto & sample: track.AttachmentSamples)
			{
				Log::Info(StringFormat("  {time: %f, name: %s},",
					sample.TimeSeconds,
					sample.AttachmentName.c_str()));
			}
		}
	}
}

}// unnamed namespace
//-----------------------------------------------------------------------
GrassBlendingGame::GrassBlendingGame(std::shared_ptr<GameHost> const& gameHostIn)
	: gameHost(gameHostIn)
{
	POMDOG_ASSERT(gameHostIn);
	graphicsContext = gameHost->GraphicsContext();
}
//-----------------------------------------------------------------------
GrassBlendingGame::~GrassBlendingGame() = default;
//-----------------------------------------------------------------------
void GrassBlendingGame::Initialize()
{
	auto window = gameHost->Window();
	window->Title("TestApp - Enjoy Game Dev, Have Fun.");
	window->AllowPlayerResizing(false);
	
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
		auto textureAtlas = assets->Load<Details::TexturePacker::TextureAtlas>("MaidChan2/skeleton.atlas");
		auto skeletonDesc = assets->Load<Details::Skeletal2D::SkeletonDesc>("MaidChan2/skeleton.json");
		maidTexture = assets->Load<Texture2D>("MaidChan2/skeleton.png");
		
		LogSkeletalInfo(textureAtlas, skeletonDesc);
		
		maidSkeleton = std::make_shared<Skeleton>(Details::Skeletal2D::CreateSkeleton(skeletonDesc.Bones));
		maidSkeletonPose = std::make_shared<SkeletonPose>(CreateSkeletonPoseBySkeleton(*maidSkeleton));
		auto animationClip = std::make_shared<AnimationClip>(Details::Skeletal2D::CreateAnimationClip(skeletonDesc, "Walk"));
		maidAnimationState = std::make_shared<AnimationState>(animationClip, 1.0f, true);
		
		maidSkin = Details::Skeletal2D::CreateSkin(skeletonDesc, textureAtlas, "default");
		maidSpriteAnimationTracks = Details::Skeletal2D::CreateSpriteAnimationTrack(skeletonDesc, textureAtlas, "Walk");
		
		animationSystem.Add(maidAnimationState, maidSkeleton, maidSkeletonPose);
	}
	
	{
		scenePanel = std::make_shared<UI::ScenePanel>(window->ClientBounds().Width, window->ClientBounds().Height);
		scenePanel->drawOrder = 1.0f;
		scenePanel->cameraObject = mainCamera;
		gameEditor->AddUIElement(scenePanel);
	}
	{
		auto stackPanel = std::make_shared<UI::StackPanel>(120, 170);
		stackPanel->drawOrder = 0.2f;
		stackPanel->Transform(Matrix3x2::CreateTranslation(Vector2{5, 10}));
		gameEditor->AddUIElement(stackPanel);

		{
			auto navigator = std::make_shared<UI::DebugNavigator>(gameHost->Clock());
			navigator->drawOrder = 0.0f;
			stackPanel->AddChild(navigator);
		}
		{
			toggleSwitch1 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch1->drawOrder = 0.0f;
			toggleSwitch1->IsOn(true);
			stackPanel->AddChild(toggleSwitch1);
			gameEditor->AddUIElement(toggleSwitch1);
		}
		{
			toggleSwitch2 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch2->drawOrder = 0.0f;
			toggleSwitch2->IsOn(true);
			stackPanel->AddChild(toggleSwitch2);
			gameEditor->AddUIElement(toggleSwitch2);
		}
		{
			toggleSwitch3 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch3->drawOrder = 0.0f;
			toggleSwitch3->IsOn(false);
			stackPanel->AddChild(toggleSwitch3);
			gameEditor->AddUIElement(toggleSwitch3);
		}
		{
			toggleSwitch4 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch4->drawOrder = 0.0f;
			toggleSwitch4->IsOn(false);
			stackPanel->AddChild(toggleSwitch4);
			gameEditor->AddUIElement(toggleSwitch4);
		}
	}
}
//-----------------------------------------------------------------------
void GrassBlendingGame::Update()
{
	auto clock = gameHost->Clock();
	auto mouse = gameHost->Mouse();
	{
		gameEditor->Update();
	}	
	
	if (toggleSwitch1->IsOn()) {
		animationSystem.Update(*clock);
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
}
//-----------------------------------------------------------------------
void GrassBlendingGame::DrawSprites()
{
	auto transform = mainCamera->Component<Transform2D>();
	auto camera = mainCamera->Component<Camera2D>();
		
	POMDOG_ASSERT(transform && camera);
	auto viewMatrix = SandboxHelper::CreateViewMatrix(*transform, *camera);;
	auto projectionMatrix = Matrix4x4::CreateOrthographicLH(
		graphicsContext->Viewport().Width(), graphicsContext->Viewport().Height(), 0.1f, 1000.0f);
	
	gameEditor->SetViewProjection(viewMatrix * projectionMatrix);

	POMDOG_ASSERT(spriteRenderer);
	spriteRenderer->Begin(SpriteSortMode::BackToFront, viewMatrix);

	auto const& globalPoses = maidSkeletonPose->GlobalPose;
	
	if (toggleSwitch3->IsOn())
	{
		for (auto & joint: *maidSkeleton)
		{
			auto & matrix = globalPoses[*joint.Index];
			spriteRenderer->Draw(texture, matrix, Vector2::Zero, {0, 0, 5, 5},
				Color::Black, MathConstants<float>::PiOver4(), {0.5f, 0.5f}, 1.0f, 2/100.0f);
			spriteRenderer->Draw(texture, matrix, Vector2::Zero, {0, 0, 2, 2},
				Color::White, MathConstants<float>::PiOver4(), {0.5f, 0.5f}, 1.0f, 1/100.0f);
			spriteRenderer->Draw(texture, matrix, Vector2::Zero, {0, 0, 32, 2},
				Color::Black, 0.0f, {0.0f, 0.5f}, 1.0f, 4/100.0f);
		}
	}

	if (toggleSwitch2->IsOn())
	{
		for (auto & slot: maidSkin.Slots())
		{
			spriteRenderer->Draw(maidTexture, globalPoses[*slot.JointIndex], slot.Translate, slot.Subrect,
				slot.Color, (slot.TextureRotate ? slot.Rotation - MathConstants<float>::PiOver2(): slot.Rotation),
				slot.Origin, slot.Scale, (maidSkin.Slots().size() - slot.DrawOrder) / maidSkin.Slots().size());
		}
	}
	
	spriteRenderer->End();
	
	if (toggleSwitch4->IsOn())
	{
		RasterizerDescription rasterizerDesc;
		rasterizerDesc.FillMode = FillMode::WireFrame;
		auto rasterizerState = std::make_shared<RasterizerState>(gameHost->GraphicsDevice(), rasterizerDesc);
		
		graphicsContext->SetRasterizerState(rasterizerState);
		spriteRenderer->Begin(SpriteSortMode::BackToFront, viewMatrix);
		
		for (auto & slot: maidSkin.Slots())
		{
			spriteRenderer->Draw(texture, globalPoses[*slot.JointIndex], slot.Translate, slot.Subrect,
				{0, 0, 0, 40},
				(slot.TextureRotate ? slot.Rotation - MathConstants<float>::PiOver2(): slot.Rotation),
				slot.Origin, slot.Scale, (maidSkin.Slots().size() - slot.DrawOrder) / maidSkin.Slots().size());
		}
		
		spriteRenderer->End();

		graphicsContext->SetRasterizerState(RasterizerState::CreateCullCounterClockwise(gameHost->GraphicsDevice()));
	}
}
//-----------------------------------------------------------------------
void GrassBlendingGame::Draw()
{
	constexpr bool enableFxaa = true;

	if (enableFxaa) {
		graphicsContext->SetRenderTarget(renderTarget);
	}
	
	graphicsContext->Clear(Color::CornflowerBlue);
	gameEditor->BeginDraw(*graphicsContext);

	graphicsContext->SetSamplerState(0, samplerPoint);
	DrawSprites();
	
	if (enableFxaa) {
		graphicsContext->SetRenderTarget();
		fxaa->Draw(*graphicsContext, renderTarget);
	}

	gameEditor->EndDraw();
	graphicsContext->Present();
}
//-----------------------------------------------------------------------
}// namespace TestApp
