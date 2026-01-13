// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SW_FogOfWarSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FFogOfWarParameter
{
	GENERATED_BODY()

	//用于识别可视性的RenderTarget
	UPROPERTY(Category="SpaceWar|Fog of War", EditDefaultsOnly)
	TObjectPtr<UTextureRenderTarget2D> RenderTarget;

	//重置颜色
	UPROPERTY(Category="SpaceWar|Fog of War", EditDefaultsOnly)
	FLinearColor ResetColor = FLinearColor(0.f, 0.f, 0.f, 1.f);

	//本体的视野大小,直接使用视野属性值
	UPROPERTY(Category="SpaceWar|Fog of War", EditDefaultsOnly)
	FVector2D VisionSize = FVector2D(1920.f, 1080.f);

	//用于附加到RenderTarget的材质,一般是圆形
	UPROPERTY(Category="SpaceWar|Fog of War", EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> VisionMaterial;
};

/**
 * 保存战争迷雾的信息,Enemy读取,Player修改
 * Player触发更新,Enemy只读取
 * 共享的数据
 */
UCLASS()
class SPACEWAR_API USW_FogOfWarSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:

private:
	// FFogOfWarParameter& FogOfWarParameterRef;

	UPROPERTY()
	TArray<uint8> FogOfWarData = {};

public:
	/*
	 * 触发更新的接口
	 */
	void UpdateFogOfWar(const FFogOfWarParameter& FogOfWarParameterRef);

	/*
	 * 获取数据的接口
	 */
	UFUNCTION()
	const TArray<uint8>& GetFogOfWarData() { return FogOfWarData; }
};
