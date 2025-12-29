// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceWar/Data/SW_BuildingType.h"
#include "SW_BuildingActor.generated.h"

enum class EBuildingGridType : uint8;

/*
 * 拥有识别网格的建造基类
 * 如果需要网格建筑,继承此基类
 */
UCLASS()
class SPACEWAR_API ASW_BuildingActor : public AActor
{
	GENERATED_BODY()

public:
	ASW_BuildingActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Building, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingMesh;

	//是否选中
	UPROPERTY()
	bool bIsSelected = false;

	//建筑所占用的网格大小
	UPROPERTY(Category=Building, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	EBuildingGridType BuildingGridType = EBuildingGridType::EBGT_1x1_Cell;

	//当前旋转角度
	UPROPERTY(Category=Building, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int CurrentRotate = 0;

	//当前FootPrint
	UPROPERTY()
	TArray<FIntPoint> CurrentFootPrint = {};

	//网格坐标,相对于网格的坐标
	UPROPERTY()
	FIntPoint GridCoord = FIntPoint();

public:
	UFUNCTION(BlueprintCallable)
	TArray<FIntPoint> GetShapeFootPrint();

	/*
	 * 用于选择改变后外观处理
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnSelectedChange(bool bInSelected);

	/*
	 * 当实际建造时,意味着PostBuilding
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnBuilded();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE bool GetIsSelected() const { return bIsSelected; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	void SetIsSelected(bool bInSelected);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE EBuildingGridType GetBuildingGridType() const { return BuildingGridType; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	FORCEINLINE void SetBuildingGridType(EBuildingGridType InBuildingGridType) { BuildingGridType = InBuildingGridType; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE int GetCurrentRotate() const { return CurrentRotate; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	FORCEINLINE void SetCurrentRotate(int InCurrentRotate) { CurrentRotate = InCurrentRotate; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE TArray<FIntPoint> GetCurrentFootPrint() const { return CurrentFootPrint; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	FORCEINLINE void SetCurrentFootPrint(TArray<FIntPoint> InCurrentFootPrint) { CurrentFootPrint = InCurrentFootPrint; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE FIntPoint GetGridCoord() const { return GridCoord; }

	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	FORCEINLINE void SetGridCoord(FIntPoint InGridCoord) { GridCoord = InGridCoord; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE UStaticMeshComponent* GetBuildingMesh() const { return BuildingMesh; }
};
