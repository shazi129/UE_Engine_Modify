#pragma once

#include "DeferredShadingRenderer.h"

class FMyFDeferredShadingSceneRenderer : public FDeferredShadingSceneRenderer
{
public:
	FMyFDeferredShadingSceneRenderer(const FSceneViewFamily* InViewFamily, FHitProxyConsumer* HitProxyConsumer);

	virtual void Render(FRHICommandListImmediate& RHICmdList) override;

	virtual void CustomRender(
		FRDGBuilder& GraphBuilder,
		FRDGTextureRef SceneColorTexture,
		FRDGTextureRef SceneDepthTexture,
		FRDGTextureRef LightShaftOcclusionTexture,
		TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTexturesWithDepth) override;
};