#include "MyRenderer/Common/MyRendererGlobalShader.h"

FMyRendererGlobalShader::FMyRendererGlobalShader() {}

FMyRendererGlobalShader::FMyRendererGlobalShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
}

bool FMyRendererGlobalShader::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{ 
	return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
}

void FMyRendererGlobalShader::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
}