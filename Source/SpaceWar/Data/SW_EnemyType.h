// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_EnemyType.generated.h"
/*
 * 敌人的类型
 */
UENUM()
enum class EEnemyType : uint8
{
	EET_General UMETA(DisplayName="普通敌人"),
	EET_Boss UMETA(DisplayName="Boss"),

	EET_Max UMETA(DisplayName="None")
};

/*
 * 用于对象池的生成参数
 */
USTRUCT(BlueprintType)
struct FEnemyPoolParameter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EEnemyType EnemyType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASW_Enemy> EnemyClass;

	UPROPERTY(EditDefaultsOnly)
	int32 Num = 0;
};
