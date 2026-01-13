// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_FogOfWarSubsystem.h"

#include "Engine/Canvas.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "SpaceWar/Building/CombatActor/SW_CombatActor.h"
#include "SpaceWar/Components/SW_GridBuildComponent.h"
#include "SpaceWar/FunctionLibrary/SW_CommonFunction.h"

void USW_FogOfWarSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("SW_FogOfWarSubsystem::Initialize,战争迷雾已启动"));
}

void USW_FogOfWarSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USW_FogOfWarSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Outer->GetWorld()->GetMapName().Contains("Combat", ESearchCase::IgnoreCase)) return false;
	return Super::ShouldCreateSubsystem(Outer);
}

void USW_FogOfWarSubsystem::UpdateFogOfWar(const FFogOfWarParameter& FogOfWarParameterRef)
{
	if (!FogOfWarParameterRef.RenderTarget) return;

	//设置 RenderTarget 的大小
	FVector2D ViewportSize = FVector2D::ZeroVector;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	if (ViewportSize == FVector2D::ZeroVector) return;
	FogOfWarParameterRef.RenderTarget->ResizeTarget(ViewportSize.X, ViewportSize.Y);

	//重置颜色
	UKismetRenderingLibrary::ClearRenderTarget2D(this, FogOfWarParameterRef.RenderTarget, FogOfWarParameterRef.ResetColor);

	/*~开始绘制 */
	//临时变量
	UCanvas* Canvas;
	FVector2D CanvasSize; //其实就是视口大小
	FDrawToRenderTargetContext CanvasContext;
	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, FogOfWarParameterRef.RenderTarget, Canvas, CanvasSize, CanvasContext);
	FVector2D CanvasCenter = CanvasSize / 2.f; //画板中心点,也是屏幕中心点
	//获取拥有者的属性值


	FVector2D VisionCenter = FogOfWarParameterRef.VisionSize / 2.f; //视野大小的中心点
	//CanvasCenter - VisionCenter代表 以左上角为原点,视野位于屏幕中心点


	//主视野的大小 VisionSize
	//绘制主视野
	Canvas->K2_DrawMaterial(
		FogOfWarParameterRef.VisionMaterial,
		CanvasCenter - VisionCenter,
		FogOfWarParameterRef.VisionSize,
		FVector2D::ZeroVector);

	//后期缓存Array
	//获取玩家Pawn
	const APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	for (ASW_BuildingActor* Element : PlayerPawn->FindComponentByClass<USW_GridBuildComponent>()->GetBuildingArray())
	{
		//识别是否是战斗组件
		if (const ASW_CombatActor* CombatActor = Cast<ASW_CombatActor>(Element))
		{
			//获取战斗建筑的屏幕坐标位置
			FVector2D ScreenPoint;
			PlayerPawn->GetLocalViewingPlayerController()->ProjectWorldLocationToScreen(CombatActor->GetActorLocation(), ScreenPoint);

			Canvas->K2_DrawMaterial(FogOfWarParameterRef.VisionMaterial,
			                        ScreenPoint - (CombatActor->GetVisionSize() / 2.f),
			                        CombatActor->GetVisionSize(),
			                        FVector2D::ZeroVector);
		}
	}

	/*~结束绘制 */
	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, CanvasContext);

	//保存绘制数据
	USW_CommonFunction::BFL_GetRenderTargetPointValue(FogOfWarParameterRef.RenderTarget, FogOfWarData);;
}
