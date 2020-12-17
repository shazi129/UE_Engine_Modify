#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"

class FMyRendererGlobalShader : public FGlobalShader
{

public:
	FMyRendererGlobalShader();

	FMyRendererGlobalShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
		FShaderCompilerEnvironment& OutEnvironment);
};
