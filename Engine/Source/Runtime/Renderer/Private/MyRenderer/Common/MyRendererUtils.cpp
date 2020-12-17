#include "MyRenderer/Common/MyRendererUtils.h"

void FMyRendererTextureVertexDesc::InitRHI()
{
	FVertexDeclarationElementList Elements;
	uint32 Stride = sizeof(FMyRendererTextureVertex);
	Elements.Add(FVertexElement(0, STRUCT_OFFSET(FMyRendererTextureVertex, Position), VET_Float4, 0, Stride));
	Elements.Add(FVertexElement(0, STRUCT_OFFSET(FMyRendererTextureVertex, UV), VET_Float2, 1, Stride));
	VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);
}

void FMyRendererTextureVertexDesc::ReleaseRHI()
{
	VertexDeclarationRHI.SafeRelease();
}

FVertexBufferRHIRef FMyRendererUtils::CreateVertexBuffer(const TArray<FVector4>& VertexList)
{
	FRHIResourceCreateInfo CreateInfo;
	FVertexBufferRHIRef VertexBufferRHI = RHICreateVertexBuffer(sizeof(FVector4) * VertexList.Num(), BUF_Volatile, CreateInfo);
	void* VoidPtr = RHILockVertexBuffer(VertexBufferRHI, 0, sizeof(FVector4) * VertexList.Num(), RLM_WriteOnly);

	FVector4* Vertices = (FVector4*)VoidPtr;

	for (int i = 0; i < VertexList.Num(); i++)
	{
		Vertices[i] = VertexList[i];
	}

	RHIUnlockVertexBuffer(VertexBufferRHI);
	return VertexBufferRHI;
}

FVertexBufferRHIRef FMyRendererUtils::CreateVertexBuffer(const TArray<FMyRendererTextureVertex>& VertexList)
{
	TResourceArray<FMyRendererTextureVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
	Vertices.SetNumUninitialized(VertexList.Num());

	for (int i = 0; i < VertexList.Num(); i++)
	{
		Vertices[i] = VertexList[i];
	}

	// Create vertex buffer. Fill buffer with initial data upon creation
	FRHIResourceCreateInfo CreateInfo(&Vertices);
	FVertexBufferRHIRef VertexBufferRHI = RHICreateVertexBuffer(Vertices.GetResourceDataSize(), BUF_Static, CreateInfo);

	return VertexBufferRHI;
}


FIndexBufferRHIRef FMyRendererUtils::CreateIndexBuffer(const uint16* Indices, uint16 NumIndices)
{
	TResourceArray<uint16, INDEXBUFFER_ALIGNMENT> IndexBuffer;

	IndexBuffer.AddUninitialized(NumIndices);
	FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint16));

	// Create index buffer. Fill buffer with initial data upon creation
	FRHIResourceCreateInfo CreateInfo(&IndexBuffer);
	FIndexBufferRHIRef IndexBufferRHI = RHICreateIndexBuffer(sizeof(uint16), IndexBuffer.GetResourceDataSize(), BUF_Static, CreateInfo);

	return IndexBufferRHI;
}