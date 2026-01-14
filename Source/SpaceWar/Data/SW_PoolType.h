// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_PoolType.generated.h"

/*
 * 用于获取子弹的参数
 */
USTRUCT(BlueprintType)
struct FBulletItemParam
{
	GENERATED_BODY()

	FBulletItemParam();


	FBulletItemParam(AActor* InNeedOwner, const FTransform& InSpawnLocation, const float InBallisticVelocity, const float InDamageRange, const float InDamage,
	                 const bool InTrackingMode, AActor* InTargetActor);

	UPROPERTY(BlueprintReadWrite)
	AActor* InNeedOwner;

	UPROPERTY(BlueprintReadWrite)
	FTransform InSpawnLocation;

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
