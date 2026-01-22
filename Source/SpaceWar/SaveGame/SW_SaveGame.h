// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SW_SaveGame.generated.h"

class ASW_BuildingActor;

enum class EBuildingGridType : uint8;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBuildingSaveData
{
	GENERATED_BODY()

public:
	// 建筑类型
	UPROPERTY()
	TSubclassOf<ASW_BuildingActor> BuildingClass;

	// 网格坐标
	UPROPERTY()
	FTransform BuildingTransform;
};

/*
 * 
 */
UCLASS()
class SPACEWAR_API USW_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, Category = "SpaceWar")
	TArray<FBuildingSaveData> BuildingSaveData;

	/*
	 * 构建函数
	 * 需要在构建的时候就设置Owner和ChildActor
	 * 简单的做法就是直接使用射线检测来设置父子关系
	 * 检测间距为1
	 * 仅适用于特殊Pawn
	 */
	UFUNCTION(BlueprintCallable)
	void ReBuildActorFromSaveGame(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void SaveBuildingToSaveGame(UObject* WorldContextObject);
};
