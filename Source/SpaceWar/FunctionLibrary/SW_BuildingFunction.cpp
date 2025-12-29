// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BuildingFunction.h"

#include "SpaceWar/Data/SW_BuildingType.h"


TArray<FIntPoint> USW_BuildingFunction::BFL_GetShapeFootPrint(EBuildingGridType BuildingGridType)
{
	switch (BuildingGridType)
	{
	case EBuildingGridType::EBGT_1x1_Cell:
		{
			return TArray<FIntPoint>{
				//单格
				FIntPoint(0, 0)
			};
		}
	case EBuildingGridType::EBGT_1x2_Cell:
		{
			return TArray<FIntPoint>{
				//双格,竖向
				FIntPoint(0, 0),
				FIntPoint(0, 1)
			};
		}
	case EBuildingGridType::EBGT_L_Cell:
		{
			return TArray<FIntPoint>{
				//L形
				FIntPoint(0, 0),
				FIntPoint(0, 1),
				FIntPoint(1, 0)
			};
		}
	case EBuildingGridType::EBGT_2x2_Cell:
		{
			return TArray<FIntPoint>{
				//4格正方形
				FIntPoint(0, 0),
				FIntPoint(0, 1),
				FIntPoint(1, 0),
				FIntPoint(1, 1)
			};
		}
	default:
		break;
	}
	return TArray<FIntPoint>();
}

void USW_BuildingFunction::BFL_RotateFootPrint(TArray<FIntPoint>& InFootPrintArray)
{
	for (FIntPoint& FootPrint : InFootPrintArray)
	{
		//这是逆时针90度
		const FIntPoint Temp = FIntPoint(-FootPrint.Y, FootPrint.X);
		// const FIntPoint Temp = FIntPoint(FootPrint.Y, -FootPrint.X); 这是顺时针90度
		
		FootPrint = Temp;
	}
}
