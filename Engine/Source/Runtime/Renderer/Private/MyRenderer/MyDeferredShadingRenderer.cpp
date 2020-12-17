
#include "MyDeferredShadingRenderer.h"
#include "MyFirstRenderPass/MyFirstRenderPass.h"

FMyFDeferredShadingSceneRenderer::FMyFDeferredShadingSceneRenderer(const FSceneViewFamily* InViewFamily, FHitProxyConsumer* HitProxyConsumer)
	: FDeferredShadingSceneRenderer(InViewFamily, HitProxyConsumer)
{

}

void FMyFDeferredShadingSceneRenderer::CustomRender(
	FRDGBuilder& GraphBuilder,
	FRDGTextureRef SceneColorTexture,
	FRDGTextureRef SceneDepthTexture,
	FRDGTextureRef LightShaftOcclusionTexture,
	TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTexturesWithDepth)
{
	MyFirstRenderPass(this, GraphBuilder, SceneColorTexture, SceneDepthTexture, LightShaftOcclusionTexture, SceneTexturesWithDepth);
}

void FMyFDeferredShadingSceneRenderer::Render(FRHICommandListImmediate& RHICmdList)
{
	FDeferredShadingSceneRenderer::Render(RHICmdList);
}
