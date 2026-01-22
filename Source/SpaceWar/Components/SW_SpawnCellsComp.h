// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceWar/Data/SW_BuildingType.h"
#include "SW_SpawnCellsComp.generated.h"


class ASW_Cell;
struct FSpawnCellParam;

/*
 * 用来生成Cells的方便组件
 * 建造等操作将会在BuildingComp中完成
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USW_SpawnCellsComp : public USceneComponent
{
	GENERATED_BODY()

public:
	USW_SpawnCellsComp();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

public:
	void InitCells();

	void ChangeCallsCollision(const bool bInCollision);

	int16 CellSize = CELL_SIZE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget))
	TArray<FSpawnCellParam> CellsParams;

	UPROPERTY()
	TArray<ASW_Cell*> Cells;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASW_Cell> CellClass;
};
