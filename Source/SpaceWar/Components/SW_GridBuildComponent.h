// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceWar/Building/SW_BuildingActor.h"
#include "SpaceWar/Building/SW_Cell.h"
#include "SW_GridBuildComponent.generated.h"

/*
 * 仅使用行优先算法网格
 * 更新为自定义建造组件,不拘泥于矩形网格
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USW_GridBuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USW_GridBuildComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/*
	 * 逻辑函数
	 */
	//当处于放置状态时,触发此函数用于旋转预览
	void RotateHeldBuilding();

	//清除高亮
	void CleanHighlight();

	//检查并且高亮放置的单元格
	bool CheckAndHighlight(const FVector& InVector, const TArray<FIntPoint>& InFootPrint);

	//放置
	void CommitBuildingToGrid();

	//取消当前所有操作
	void CancelCurrentAction();

	//在网格上选择建筑物
	void SelectBuildingOnGrid(ASW_BuildingActor* InBuilding);

	//不选择Building
	void UnSelectBuild();

	//删除选中的建筑
	void DeleteSelectBuilding();

	//更新鼠标下的建筑物位置
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

	EBuildingCompState CurrentBuildingState = EBuildingCompState::EBCS_Idle;

	UPROPERTY()
	TObjectPtr<ASW_BuildingActor> SelectedBuilding = nullptr;
	UPROPERTY()
	TObjectPtr<ASW_BuildingActor> HeldBuilding = nullptr;

	int32 CheckRange = 10;

public:
	UFUNCTION(BlueprintCallable)
	void Rotate_Handle();
	UFUNCTION(BlueprintCallable)
	void Delete_Handle();
	UFUNCTION(BlueprintCallable)
	void Confirm_Handle();
	UFUNCTION(BlueprintCallable)
	void Cancel_Handle();
};
