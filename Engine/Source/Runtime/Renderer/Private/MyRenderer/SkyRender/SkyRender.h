#pragma once

#include "ShaderParameterStruct.h"
#include "MyRenderer/Common/MyRendererGlobalShader.h"

class FSkyRenderVS : public FMyRendererGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSkyRenderVS);

	FSkyRenderVS() {};

	FSkyRenderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FMyRendererGlobalShader(Initializer){};
};

template<uint8 SimpleLevel>
class FSkyRenderPS : public FMyRendererGlobalShader
{
public:

	DECLARE_GLOBAL_SHADER(FSkyRenderPS);


	FSkyRenderPS() {};

	FSkyRenderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FMyRendererGlobalShader(Initializer) {};

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FMyRendererGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		OutEnvironment.SetDefine(TEXT("SAMPLE_LEVEL"), SimpleLevel);
	}
};


void SkyRenderPass(
	FSceneRenderer* SceneRenderer,
	FRDGBuilder& GraphBuilder,
	FRDGTextureRef SceneColorTexture,
	FRDGTextureRef SceneDepthTexture,
	FRDGTextureRef LightShaftOcclusionTexture,
	TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTexturesWithDepth);
