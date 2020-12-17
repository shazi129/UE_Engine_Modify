#pragma once

#include "ShaderParameterStruct.h"
#include "MyRenderer/Common/MyRendererGlobalShader.h"


void MyFirstRenderPass(
	FSceneRenderer* SceneRenderer,
	FRDGBuilder& GraphBuilder,
	FRDGTextureRef SceneColorTexture,
	FRDGTextureRef SceneDepthTexture,
	FRDGTextureRef LightShaftOcclusionTexture,
	TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTexturesWithDepth);

class FMyFirstRenderPassVS : public FMyRendererGlobalShader
{
	DECLARE_GLOBAL_SHADER(FMyFirstRenderPassVS);

public:
	FMyFirstRenderPassVS() {};

	FMyFirstRenderPassVS(const CompiledShaderInitializerType& Initializer)
		: FMyRendererGlobalShader(Initializer)
	{}
};

class FMyFirstRenderPassPS : public FMyRendererGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FMyFirstRenderPassPS);
	SHADER_USE_PARAMETER_STRUCT(FMyFirstRenderPassPS, FMyRendererGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};