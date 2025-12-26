// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SW_BuildingFunction.generated.h"

enum class EBuildingGridType : uint8;

/**
 * 用于建造系统的函数库
 */
UCLASS()
class SPACEWAR_API USW_BuildingFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	 * 用于获取建筑占用格子的坐标
	 * 根据格子的类型,返回对应的原生坐标数组
	 */
	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	static TArray<FIntPoint> BFL_GetShapeFootPrint(EBuildingGridType BuildingGridType);

	/*
	 * 每次调用都会逆时针旋转90度
	 * 根据笛卡尔坐标系进行变换
	 */
	UFUNCTION(BlueprintCallable, Category = "SpaceWar")
	static void BFL_RotateFootPrint(TArray<FIntPoint>& InFootPrintArray);
};
