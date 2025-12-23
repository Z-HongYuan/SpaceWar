// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SW_GridBuildComponent.generated.h"

/*
 * 1. 定义 FIntPoint 为网格块坐标 本质为 Int 类型的2D向量
 */
// #define FGridCoord FIntPoint

/*
 * 单个网格块的状态
 */
UENUM()
enum class EGridState : uint8
{
	EGS_Locked UMETA(DisplayName="已锁定"), // 不可用
	EGS_Unlocked UMETA(DisplayName="可建造"), // 可建造
	EGS_Occupied UMETA(DisplayName="已建造"), // 已建造

	EGS_Max UMETA(DisplayName="None")
};

/*
 * 单个网格块
 */
USTRUCT()
struct FGridCell
{
	GENERATED_BODY()

public:
	FGridCell() = default;

	FGridCell(const FIntPoint InPosition, const EGridState InState, const TSoftObjectPtr<UStaticMesh> InGridMesh)
	{
		Position = InPosition;
		State = InState;
		GridMesh = InGridMesh;
	}

	FIntPoint Position = FIntPoint();
	EGridState State = EGridState::EGS_Locked;
	TSoftObjectPtr<UStaticMesh> GridMesh = nullptr;
};


/*
 * 网格建造组件
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
	 * 总体的网格表
	 */
	UPROPERTY()
	TMap<FIntPoint, FGridCell> GridCells = {};

	/*
	 * 从数据表中初始化格子
	 * 仅 读取所有格子的位置，状态默认为锁定
	 */
	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateGridCells();

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TSoftObjectPtr<UStaticMesh> GridMesh;

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float GridSize = 100.f;

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool bDebug = false;

	void Debug();

public:
	FORCEINLINE TMap<FIntPoint, FGridCell>& GetGridCells() { return GridCells; }
	FORCEINLINE void CleanGridCells() { GridCells.Empty(); }
};
