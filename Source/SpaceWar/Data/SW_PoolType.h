// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceWar/Enemy/SW_EnemyPoolItem.h"
#include "SW_PoolType.generated.h"

/*--------------------------子弹对象池------------------------------------*/

//设置子弹时的必要参数
USTRUCT(BlueprintType)
struct FBulletItemParam
{
	GENERATED_BODY()

	FBulletItemParam();


	FBulletItemParam(AActor* InNeedOwner, const FTransform& InSpawnTransform, const float InBallisticVelocity, const float InDamageRange, const float InDamage,
	                 const bool InTrackingMode, AActor* InTargetActor);

	UPROPERTY(BlueprintReadWrite)
	AActor* InNeedOwner;

	UPROPERTY(BlueprintReadWrite)
	FTransform InSpawnTransform;

	UPROPERTY(BlueprintReadWrite)
	float BallisticVelocity;

	UPROPERTY(BlueprintReadWrite)
	float DamageRange;

	UPROPERTY(BlueprintReadWrite)
	float Damage;

	UPROPERTY(BlueprintReadWrite)
	bool TrackingMode;

	UPROPERTY(BlueprintReadWrite)
	AActor* TargetActor;
};


/*-----------------------敌人对象池----------------------------------*/

//敌人的类型枚举
UENUM()
enum class EEnemyType : uint8
{
	EET_General UMETA(DisplayName="普通敌人"),
	EET_Boss UMETA(DisplayName="Boss"),

	EET_Max UMETA(DisplayName="None")
};

//敌人对象池的生成参数,针对于Pool
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

//敌人对象池的传递参数,针对于Items
USTRUCT(BlueprintType)
struct FEnemyItemParam
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadWrite)
	FTransform InSpawnTransform;

	UPROPERTY(BlueprintReadWrite)
	float InHealth;
};
