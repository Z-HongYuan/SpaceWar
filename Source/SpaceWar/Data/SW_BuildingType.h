#pragma once

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

UENUM()
enum class EBuildingState : uint8
{
	EBS_Idle UMETA(DisplayName="空闲"),
	EBS_Building UMETA(DisplayName="放置状态"),
	EBS_Selecting UMETA(DisplayName="选择状态"),

	EBS_Max UMETA(DisplayName="None")
};
