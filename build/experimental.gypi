{
  'variables': {
    'pomdog_expr_dir': '../experimental/Pomdog.Experimental',
    'pomdog_experimental_2d_sources': [
      '<@(pomdog_expr_dir)/Pomdog2D.hpp',

      '<@(pomdog_expr_dir)/Gameplay2D/Animator.cpp',
      '<@(pomdog_expr_dir)/Gameplay2D/Animator.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/BeamRenderable.cpp',
      '<@(pomdog_expr_dir)/Gameplay2D/BeamRenderable.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/Behavior.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/Camera2D.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/GameLevel.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/ParticleRenderable.cpp',
      '<@(pomdog_expr_dir)/Gameplay2D/ParticleRenderable.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/Renderable.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/ScriptBehavior.cpp',
      '<@(pomdog_expr_dir)/Gameplay2D/ScriptBehavior.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/SkinnedMeshRenderable.cpp',
      '<@(pomdog_expr_dir)/Gameplay2D/SkinnedMeshRenderable.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/SpriteRenderable.cpp',
      '<@(pomdog_expr_dir)/Gameplay2D/SpriteRenderable.hpp',
      '<@(pomdog_expr_dir)/Gameplay2D/Transform2D.hpp',

      '<@(pomdog_expr_dir)/Graphics/FXAA.cpp',
      '<@(pomdog_expr_dir)/Graphics/FXAA.hpp',
      '<@(pomdog_expr_dir)/Graphics/LineBatch.cpp',
      '<@(pomdog_expr_dir)/Graphics/LineBatch.hpp',
      '<@(pomdog_expr_dir)/Graphics/PolygonBatch.cpp',
      '<@(pomdog_expr_dir)/Graphics/PolygonBatch.hpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteBatch.cpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteBatch.hpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteFont.cpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteFont.hpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteFontLoader.cpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteFontLoader.hpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteLine.cpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteLine.hpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteSortMode.hpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteRenderer.cpp',
      '<@(pomdog_expr_dir)/Graphics/SpriteRenderer.hpp',
      '<@(pomdog_expr_dir)/Graphics/TextureRegion.hpp',

      '<@(pomdog_expr_dir)/InGameEditor/InGameEditor.cpp',
      '<@(pomdog_expr_dir)/InGameEditor/InGameEditor.hpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/EditorColorScheme.hpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/GradientPlane.cpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/GradientPlane.hpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/PrimitiveAxes.cpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/PrimitiveAxes.hpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/PrimitiveGrid.cpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/PrimitiveGrid.hpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/SpriteDrawingContext.cpp',
      '<@(pomdog_expr_dir)/InGameEditor/detail/SpriteDrawingContext.hpp',

      '<@(pomdog_expr_dir)/Particle2D/Beam.hpp',
      '<@(pomdog_expr_dir)/Particle2D/BeamEmitter.hpp',
      '<@(pomdog_expr_dir)/Particle2D/BeamSystem.cpp',
      '<@(pomdog_expr_dir)/Particle2D/BeamSystem.hpp',
      '<@(pomdog_expr_dir)/Particle2D/Particle.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleCurveKey.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleCurveLerp.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleEmitter.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleEmitterShape.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleEmitterShapeBox.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleEmitterShapeSector.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleParameter.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleParameterConstant.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleParameterCurve.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleParameterRandom.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleParameterRandomCurves.hpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleSystem.cpp',
      '<@(pomdog_expr_dir)/Particle2D/ParticleSystem.hpp',

      '<@(pomdog_expr_dir)/Skeletal2D/AnimationAdditiveNode.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationAdditiveNode.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationBlendInput.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationBlendInputType.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationClip.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationClip.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationClipNode.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationClipNode.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationGraph.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationGraphWeight.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationGraphWeight.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationGraphWeightCollection.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationGraphWeightCollection.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationLerpNode.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationLerpNode.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationNode.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationState.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationState.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationSystem.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationSystem.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationTimeInterval.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationTimer.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationTimer.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationTrack.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/AnimationTrack.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/CompressedFloat.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/Joint.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/JointIndex.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/JointPose.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/RigidSlot.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/RotationTrack.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/ScaleTrack.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/Skeleton.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/Skeleton.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkeletonHelper.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkeletonHelper.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkeletonPose.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkeletonPose.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkeletonTransform.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/Skin.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/Skin.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkinnedMesh.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkinnedMeshPart.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SkinnedVertex.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SpriteAnimationTrack.cpp',
      '<@(pomdog_expr_dir)/Skeletal2D/SpriteAnimationTrack.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/TranslationTrack.hpp',
      '<@(pomdog_expr_dir)/Skeletal2D/detail/AnimationKeyHelper.hpp',

      '<@(pomdog_expr_dir)/Spine/AnimationGraphBuilder.cpp',
      '<@(pomdog_expr_dir)/Spine/AnimationGraphBuilder.hpp',
      '<@(pomdog_expr_dir)/Spine/AnimationLoader.cpp',
      '<@(pomdog_expr_dir)/Spine/AnimationLoader.hpp',
      '<@(pomdog_expr_dir)/Spine/SkeletonDesc.hpp',
      '<@(pomdog_expr_dir)/Spine/SkeletonDescLoader.cpp',
      '<@(pomdog_expr_dir)/Spine/SkeletonDescLoader.hpp',
      '<@(pomdog_expr_dir)/Spine/SkeletonLoader.cpp',
      '<@(pomdog_expr_dir)/Spine/SkeletonLoader.hpp',
      '<@(pomdog_expr_dir)/Spine/SkinLoader.cpp',
      '<@(pomdog_expr_dir)/Spine/SkinLoader.hpp',
      '<@(pomdog_expr_dir)/Spine/SkinnedMeshLoader.cpp',
      '<@(pomdog_expr_dir)/Spine/SkinnedMeshLoader.hpp',
      '<@(pomdog_expr_dir)/Spine/SpriteAnimationLoader.cpp',
      '<@(pomdog_expr_dir)/Spine/SpriteAnimationLoader.hpp',

      '<@(pomdog_expr_dir)/TexturePacker/TextureAtlas.hpp',
      '<@(pomdog_expr_dir)/TexturePacker/TextureAtlasLoader.cpp',
      '<@(pomdog_expr_dir)/TexturePacker/TextureAtlasLoader.hpp',

      '<@(pomdog_expr_dir)/Rendering/ParticleBatchCommand.cpp',
      '<@(pomdog_expr_dir)/Rendering/ParticleBatchCommand.hpp',
      '<@(pomdog_expr_dir)/Rendering/RenderCommand.hpp',
      '<@(pomdog_expr_dir)/Rendering/Renderer.cpp',
      '<@(pomdog_expr_dir)/Rendering/Renderer.hpp',
      '<@(pomdog_expr_dir)/Rendering/RenderQueue.cpp',
      '<@(pomdog_expr_dir)/Rendering/RenderQueue.hpp',
      '<@(pomdog_expr_dir)/Rendering/SkinnedMeshCommand.cpp',
      '<@(pomdog_expr_dir)/Rendering/SkinnedMeshCommand.hpp',
      '<@(pomdog_expr_dir)/Rendering/SpriteBatchRenderer.cpp',
      '<@(pomdog_expr_dir)/Rendering/SpriteBatchRenderer.hpp',
      '<@(pomdog_expr_dir)/Rendering/SpriteCommand.cpp',
      '<@(pomdog_expr_dir)/Rendering/SpriteCommand.hpp',

      '<@(pomdog_expr_dir)/UI/Control.hpp',
      '<@(pomdog_expr_dir)/UI/DrawingContext.hpp',
      '<@(pomdog_expr_dir)/UI/DebugNavigator.cpp',
      '<@(pomdog_expr_dir)/UI/DebugNavigator.hpp',
      '<@(pomdog_expr_dir)/UI/HorizontalAlignment.hpp',
      '<@(pomdog_expr_dir)/UI/Panel.hpp',
      '<@(pomdog_expr_dir)/UI/PointerEventType.hpp',
      '<@(pomdog_expr_dir)/UI/PointerPoint.hpp',
      '<@(pomdog_expr_dir)/UI/ScenePanel.cpp',
      '<@(pomdog_expr_dir)/UI/ScenePanel.hpp',
      '<@(pomdog_expr_dir)/UI/Slider.cpp',
      '<@(pomdog_expr_dir)/UI/Slider.hpp',
      '<@(pomdog_expr_dir)/UI/StackPanel.cpp',
      '<@(pomdog_expr_dir)/UI/StackPanel.hpp',
      '<@(pomdog_expr_dir)/UI/TextBlock.cpp',
      '<@(pomdog_expr_dir)/UI/TextBlock.hpp',
      '<@(pomdog_expr_dir)/UI/Thickness.hpp',
      '<@(pomdog_expr_dir)/UI/ToggleSwitch.cpp',
      '<@(pomdog_expr_dir)/UI/ToggleSwitch.hpp',
      '<@(pomdog_expr_dir)/UI/UIElement.hpp',
      '<@(pomdog_expr_dir)/UI/UIElementHierarchy.cpp',
      '<@(pomdog_expr_dir)/UI/UIElementHierarchy.hpp',
      '<@(pomdog_expr_dir)/UI/UIEventDispatcher.cpp',
      '<@(pomdog_expr_dir)/UI/UIEventDispatcher.hpp',
      '<@(pomdog_expr_dir)/UI/UIEventListener.hpp',
      '<@(pomdog_expr_dir)/UI/UIHelper.hpp',
      '<@(pomdog_expr_dir)/UI/UIView.cpp',
      '<@(pomdog_expr_dir)/UI/UIView.hpp',
      '<@(pomdog_expr_dir)/UI/VerticalAlignment.hpp',
      '<@(pomdog_expr_dir)/UI/detail/SubscribeRequestDispatcher.hpp',
      '<@(pomdog_expr_dir)/UI/detail/UIEventConnection.hpp',
    ],
  },
}
