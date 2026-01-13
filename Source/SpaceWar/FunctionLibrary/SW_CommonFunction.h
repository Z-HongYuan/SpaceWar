// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SW_CommonFunction.generated.h"


/**
 * 
 */
UCLASS()
class SPACEWAR_API USW_CommonFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	static USaveGame* BFL_GetSaveGameObject(const FString& SlotName, const int32 UserIndex, TSubclassOf<USaveGame> SaveGameClass);

	/*
	 * 获取渲染目标输入所有的R通道值,特别不建议Tick
	 */
	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	static bool BFL_GetRenderTargetPointValue(UTextureRenderTarget2D* RenderTarget, TArray<uint8>& OutValue);
};
