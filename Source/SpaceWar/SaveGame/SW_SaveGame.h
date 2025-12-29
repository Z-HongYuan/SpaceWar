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
	// 建筑类型（不是 Actor 指针）EBuildingGridType
	UPROPERTY()
	TSubclassOf<ASW_BuildingActor> BuildingClass;

	//类型
	UPROPERTY()
	EBuildingGridType BuildingGridType;

	UPROPERTY()
	FRotator CurrentRotate;

	// 网格坐标
	UPROPERTY()
	FIntPoint GridCoord;
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
};
