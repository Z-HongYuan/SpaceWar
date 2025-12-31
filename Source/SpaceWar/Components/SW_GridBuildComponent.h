// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceWar/Building/SW_BuildingActor.h"
#include "SpaceWar/Building/SW_Cell.h"
#include "SW_GridBuildComponent.generated.h"

class USaveGame;
/*
 * 仅使用行优先算法网格
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USW_GridBuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USW_GridBuildComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	/*
	 * 网格的Helper函数/辅助器
	 */
	UFUNCTION()
	FVector GetGridOrigin();

	UFUNCTION()
	FIntPoint GetPointFromWorldLocation(const FVector& InLocation);

	UFUNCTION()
	FVector GetWorldLocationFromPoint(const FIntPoint& InPoint);

	UFUNCTION()
	bool IsValidPoint(const FIntPoint& InPoint);

	UFUNCTION()
	ASW_Cell* GetCellFromPoint(const FIntPoint& InPoint);

	UFUNCTION()
	ASW_Cell* GetCellFromWorldLocation(const FVector& InLocation);

	/*
	 * 逻辑函数
	 */
	//当处于放置状态时,触发此函数用于旋转预览
	UFUNCTION()
	void RotateHeldBuilding();

	//清除高亮
	UFUNCTION()
	void CleanHighlight();

	//检查并且高亮放置的单元格
	UFUNCTION()
	bool CheckAndHighlight(const FIntPoint& InPoint, const TArray<FIntPoint>& InFootPrint);

	//放置
	UFUNCTION()
	void CommitBuildingToGrid();

	//取消当前所有操作
	UFUNCTION()
	void CancelCurrentAction();

	//在网格上选择建筑物
	UFUNCTION()
	void SelectBuildingOnGrid(ASW_BuildingActor* InBuilding);

	//不选择Building
	UFUNCTION()
	void UnSelectBuild();

	//删除选中的建筑
	UFUNCTION()
	void DeleteSelectBuilding();

	//更新鼠标下的建筑物位置
	UFUNCTION()
	void UpdateCursorBuildingLocation();

	//生成一个建筑物
	UFUNCTION(BlueprintCallable)
	void SpawnAndAttachBuilding(TSubclassOf<ASW_BuildingActor> InBuildingClass);
	/*
	 * 使用的Temp变量
	 */
	UPROPERTY()
	TArray<ASW_Cell*> GridArray = {};
	UPROPERTY()
	TArray<ASW_Cell*> PreHighlightArray = {};
	UPROPERTY()
	EBuildingState CurrentBuildingState = EBuildingState::EBS_Idle;

	UPROPERTY()
	TObjectPtr<ASW_BuildingActor> SelectedBuilding = nullptr;
	UPROPERTY()
	TObjectPtr<ASW_BuildingActor> HeldBuilding = nullptr;

public:
	/*
	 * 初始化网格
	 * 目前是通过长宽创建矩形
	 * 后期可能会通过数据创建不规则网格
	 */
	UFUNCTION()
	void InitGrid();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	int32 Height = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	int32 Width = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	float CellSize = 100.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	TSubclassOf<ASW_Cell> CellClass;

	UFUNCTION(BlueprintCallable)
	void Rotate_Handle();
	UFUNCTION(BlueprintCallable)
	void Delete_Handle();
	UFUNCTION(BlueprintCallable)
	void Confirm_Handle();
	UFUNCTION(BlueprintCallable)
	void Cancel_Handle();

	UFUNCTION(BlueprintCallable)
	void ReBuildActorFromSaveGame(USaveGame* InSaveGame, USaveGame*& OutSaveGame);

	UFUNCTION(BlueprintCallable)
	void SaveActorToSaveGame(USaveGame* InSaveGame, USaveGame*& OutSaveGame);
};
