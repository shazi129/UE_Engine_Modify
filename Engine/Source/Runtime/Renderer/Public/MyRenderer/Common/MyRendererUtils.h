#pragma once

#include "CoreMinimal.h"

struct FMyRendererTextureVertex
{
	FVector4 Position;
	FVector2D UV;

	FMyRendererTextureVertex(FVector4 ParamPos, FVector2D ParamUV)
	{
		Position = ParamPos;
		UV = ParamUV;
	}
};


class FMyRendererTextureVertexDesc : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;

	virtual void InitRHI() override;

	virtual void ReleaseRHI() override;
};


class FMyRendererUtils
{
public:

	static FVertexBufferRHIRef CreateVertexBuffer(const TArray<FVector4>& VertexList);

	static FVertexBufferRHIRef CreateVertexBuffer(const TArray<FMyRendererTextureVertex>& VertexList);

	static FIndexBufferRHIRef CreateIndexBuffer(const uint16* Indices, uint16 NumIndices);
};
