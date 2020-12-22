#include "SkyRender.h"


IMPLEMENT_SHADER_TYPE(, FSkyRenderVS, TEXT("/Engine/MyShader/SkyRender.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(template<>, FSkyRenderPS<0>, TEXT("/Engine/MyShader/SkyRender.usf"), TEXT("MainPS"), SF_Pixel);
IMPLEMENT_SHADER_TYPE(template<>, FSkyRenderPS<1>, TEXT("/Engine/MyShader/SkyRender.usf"), TEXT("MainPS"), SF_Pixel);
IMPLEMENT_SHADER_TYPE(template<>, FSkyRenderPS<2>, TEXT("/Engine/MyShader/SkyRender.usf"), TEXT("MainPS"), SF_Pixel);


void SkyRenderPass(
	FSceneRenderer* SceneRenderer,
	FRDGBuilder& GraphBuilder,
	FRDGTextureRef SceneColorTexture,
	FRDGTextureRef SceneDepthTexture,
	FRDGTextureRef LightShaftOcclusionTexture,
	TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTexturesWithDepth)
{

}
