#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SW_BuildingType.generated.h"

/*
 * 单元格状态
 * 需要改变BuildingComponent里面的Check
 */
UENUM()
enum class ECellState : uint8
{
	ECS_Idle UMETA(DisplayName="空闲"),
	ECS_CanBuild UMETA(DisplayName="可放置"),
	ECS_CannotBuild UMETA(DisplayName="不可放置"),

	ECS_Max UMETA(DisplayName="None")
};

/*
 * 本质上大概就只支持这些
 * 如果要更改
 * 1. 需要改变蓝图函数库中Switch参数 GetShapeFootPrint()
 */
UENUM()
enum class EBuildingGridType : uint8
{
	EBGT_1x1_Cell UMETA(DisplayName="1x1格"),
	EBGT_1x2_Cell UMETA(DisplayName="1x2格"),
	EBGT_L_Cell UMETA(DisplayName="L格"),
	EBGT_2x2_Cell UMETA(DisplayName="2x2格"),

	EBT_Max UMETA(DisplayName="None")
};

/*
 * 新建筑组件使用的状态,标记组件处于的建造状态
 */
UENUM()
enum class EBuildingCompState : uint8
{
	EBCS_Idle UMETA(DisplayName="空闲"),
	EBCS_Building UMETA(DisplayName="放置状态"),
	EBCS_Selecting UMETA(DisplayName="选择状态"),

	EBCS_Max UMETA(DisplayName="None")
};

/*
 * 未使用,推进器的方位问题由Dot公式处理
UENUM()
enum class EBuildingDirection : uint8
{
	EBD_Forward UMETA(DisplayName="向前"),
	EBD_Backward UMETA(DisplayName="向后"),
	EBD_Left UMETA(DisplayName="向左"),
	EBD_Right UMETA(DisplayName="向右"),

	EBD_Max UMETA(DisplayName="None")
};
*/

#define CELL_SIZE 100

/*
 * 用于批量生成Cell的参数
 */
USTRUCT(BlueprintType)
struct FSpawnCellParam
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget))
	FVector CellLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget))
	FGameplayTagContainer CellTags;
};
