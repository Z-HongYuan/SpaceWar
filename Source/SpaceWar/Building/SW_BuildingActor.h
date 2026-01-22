// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceWar/Data/SW_BuildingType.h"
#include "SW_BuildingActor.generated.h"

/*
 * 拥有识别网格的建造基类
 * 如果需要网格建筑,继承此基类
 */
UCLASS(Abstract)
class SPACEWAR_API ASW_BuildingActor : public AActor
{
	GENERATED_BODY()

public:
	ASW_BuildingActor();

private:
	UPROPERTY(Category=Building, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingMesh;

	//是否选中
	bool bIsSelected = false;

	//建筑所占用的网格大小
	UPROPERTY(Category=Building, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	EBuildingGridType BuildingGridType = EBuildingGridType::EBGT_1x1_Cell;

	//当前旋转角度
	int CurrentRotate = 0;

	UPROPERTY(Category=Building, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	FGameplayTag BuildingTag;

public:
	//用于选择改变后外观处理
	UFUNCTION(BlueprintImplementableEvent)
	void OnSelectedChange(bool bInSelected);

	TArray<FIntPoint> GetShapeFootPrint();

	//当实际建造时,意味着PostBuilding
	virtual void OnBuilded();
	UFUNCTION(BlueprintImplementableEvent)
	void K2_OnBuilded();

	FORCEINLINE bool GetIsSelected() const { return bIsSelected; }
	void SetIsSelected(bool bInSelected);
	FORCEINLINE EBuildingGridType GetBuildingGridType() const { return BuildingGridType; }
	FORCEINLINE int GetCurrentRotate() const { return CurrentRotate; }
	FORCEINLINE void SetCurrentRotate(int InCurrentRotate) { CurrentRotate = InCurrentRotate; }
	FORCEINLINE const FGameplayTag& GetBuildingTag() const { return BuildingTag; }
};
