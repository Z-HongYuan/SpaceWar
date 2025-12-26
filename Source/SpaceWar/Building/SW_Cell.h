// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceWar/Data/BuildingType.h"
#include "SW_Cell.generated.h"

/*
 * 基础单元格
 * 拥有被占用,状态,坐标
 */
UCLASS()
class SPACEWAR_API ASW_Cell : public AActor
{
	GENERATED_BODY()

public:
	ASW_Cell();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> CellMesh;

	//是否被占用
	UPROPERTY()
	bool bIsOccupied = false;

	//单元格状态
	UPROPERTY()
	ECellState CellState = ECellState::ECS_Idle;

	//单元格坐标
	UPROPERTY()
	FIntPoint CellPosition = FIntPoint();

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "SpaceWar")
	void OnCellStateChanged(ECellState InCellState);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE bool GetIsOccupied() const { return bIsOccupied; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	FORCEINLINE void SetIsOccupied(const bool& InIsOccupied) { bIsOccupied = InIsOccupied; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE ECellState GetCellState() const { return CellState; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	void SetCellState(const ECellState& InCellState);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE FIntPoint GetCellPosition() const { return CellPosition; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	FORCEINLINE void SetCellPosition(const FIntPoint& InCellPosition) { CellPosition = InCellPosition; }
};
