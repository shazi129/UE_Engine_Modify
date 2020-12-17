#include "MyFirstRenderPass.h"
#include "MyRenderer/Common/MyRendererUtils.h"
#include "PostProcess/SceneRenderTargets.h"
#include "SceneRendering.h"
#include "ScreenPass.h"

IMPLEMENT_SHADER_TYPE(, FMyFirstRenderPassVS, TEXT("/Engine/MyShader/GreenColor.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FMyFirstRenderPassPS, TEXT("/Engine/MyShader/GreenColor.usf"), TEXT("MainPS"), SF_Pixel);

void MyFirstRenderPass(
	FSceneRenderer* SceneRenderer,
	FRDGBuilder& GraphBuilder,
	FRDGTextureRef SceneColorTexture,
	FRDGTextureRef SceneDepthTexture,
	FRDGTextureRef LightShaftOcclusionTexture,
	TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTexturesWithDepth)
{

 	for (int32 ViewIndex = 0; ViewIndex < SceneRenderer->Views.Num(); ViewIndex++)
 	{
 		const FViewInfo& View = SceneRenderer->Views[ViewIndex];
 
 		if (View.IsPerspectiveProjection() == false)
 		{
 			continue;
 		}

		FIntRect Viewport = View.ViewRect;
		TShaderMapRef<FMyFirstRenderPassVS> VertexShader(View.ShaderMap);
		TShaderMapRef<FMyFirstRenderPassPS> PixelShader(View.ShaderMap);

		FMyFirstRenderPassPS::FParameters* PassParameter = GraphBuilder.AllocParameters<FMyFirstRenderPassPS::FParameters>();
		PassParameter->RenderTargets[0] = FRenderTargetBinding(SceneColorTexture, ERenderTargetLoadAction::ELoad);
		ClearUnusedGraphResources(PixelShader, PassParameter);

		GraphBuilder.AddPass({}, PassParameter, ERDGPassFlags::Raster, [Viewport, VertexShader, PixelShader](FRHICommandList& RHICmdListLambda)
			{
				FGraphicsPipelineStateInitializer GraphicsPSOInit;
				RHICmdListLambda.ApplyCachedRenderTargets(GraphicsPSOInit);
				RHICmdListLambda.SetViewport(Viewport.Min.X, Viewport.Min.Y, 0.0f, Viewport.Max.X, Viewport.Max.Y, 1.0f);

				GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
				GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGB, BO_Add, BF_One, BF_SourceAlpha>::GetRHI();
				GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
				GraphicsPSOInit.PrimitiveType = PT_TriangleList;

				FMyRendererTextureVertexDesc VertexDec;
				VertexDec.InitRHI();
				GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDec.VertexDeclarationRHI;

				GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
				GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();

				SetGraphicsPipelineState(RHICmdListLambda, GraphicsPSOInit);

				TArray<FMyRendererTextureVertex> VertexList;
				VertexList.Add(FMyRendererTextureVertex(FVector4(1, 1, 0, 1), FVector2D(1, 1)));
				VertexList.Add(FMyRendererTextureVertex(FVector4(-1, 1, 0, 1), FVector2D(0, 1)));
				VertexList.Add(FMyRendererTextureVertex(FVector4(1, -1, 0, 1), FVector2D(1, 0)));
				VertexList.Add(FMyRendererTextureVertex(FVector4(-1, -1, 0, 1), FVector2D(0, 0)));
				FVertexBufferRHIRef VertexBufferRHI = FMyRendererUtils::CreateVertexBuffer(VertexList);

				static const uint16 Indices[6] =
				{
						0, 1, 2,
						2, 1, 3
				};
				FIndexBufferRHIRef IndexBuffRHI = FMyRendererUtils::CreateIndexBuffer(Indices, 6);

				RHICmdListLambda.SetStreamSource(0, VertexBufferRHI, 0);
				RHICmdListLambda.DrawIndexedPrimitive(IndexBuffRHI, 0, 0, 4, 0, 2, 1);
			});
 	}

#if WITH_EDITOR
	for (int32 ViewIndex = 0; ViewIndex < SceneRenderer->Views.Num(); ViewIndex++)
	{
		const FViewInfo& View = SceneRenderer->Views[ViewIndex];

		AddDrawCanvasPass(GraphBuilder, {}, View, FScreenPassRenderTarget(SceneColorTexture, View.ViewRect, ERenderTargetLoadAction::ELoad),
			[&View](FCanvas& Canvas)
			{
				const float ViewPortWidth = float(View.ViewRect.Width());
				const float ViewPortHeight = float(View.ViewRect.Height());
				FLinearColor TextColor(1.0f, 0.0f, 0.0f);
				FString Text = TEXT("In MyFirstRenderPass::MyFirstRenderPass");
				Canvas.DrawShadowedString(ViewPortWidth * 0.5f - Text.Len() * 7.0f, ViewPortHeight * 0.4f, *Text, GetStatsFont(), TextColor);
			});
	}
#endif
}