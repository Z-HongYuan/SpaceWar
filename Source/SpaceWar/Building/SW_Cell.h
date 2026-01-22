// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceWar/Data/SW_BuildingType.h"
#include "SW_Cell.generated.h"

/*
 * 基础单元格
 * 拥有被占用,状态,坐标
 */
UCLASS(Abstract)
class SPACEWAR_API ASW_Cell : public AActor
{
	GENERATED_BODY()

public:
	ASW_Cell();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> CellMesh;

	//是否被占用
	bool bIsOccupied = false;

	//单元格状态
	ECellState CellState = ECellState::ECS_Idle;

	//允许放置的建筑类型
	FGameplayTagContainer AllowTags;

public:
	//观察者模式的指向建筑在Cell之上的指针
	UPROPERTY()
	TWeakObjectPtr<AActor> OccupiedActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	bool bIsDebug = false;

	/*~暴露的事件*/
	UFUNCTION(BlueprintImplementableEvent, Category = "SpaceWar")
	void OnCellStateChanged(ECellState InCellState);

	/*~C++内部使用*/
	FORCEINLINE bool GetIsOccupied() const { return bIsOccupied; }
	FORCEINLINE void SetIsOccupied(const bool& InIsOccupied) { bIsOccupied = InIsOccupied; }
	FORCEINLINE ECellState GetCellState() const { return CellState; }
	void SetCellState(const ECellState& InCellState);
	FORCEINLINE const FGameplayTagContainer& GetAllowTags() const { return AllowTags; }
	FORCEINLINE void SetAllowTags(const FGameplayTagContainer& InAllowTags) { AllowTags = InAllowTags; }
	FORCEINLINE void AddAllowTag(const FGameplayTag& InTag) { AllowTags.AddTag(InTag); }
	FORCEINLINE void RemoveAllowTag(const FGameplayTag& InTag) { AllowTags.RemoveTag(InTag); }
};
