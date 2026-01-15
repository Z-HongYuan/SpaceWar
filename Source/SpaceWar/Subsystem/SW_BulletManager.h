// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceWar/Data/SW_PoolType.h"
#include "Subsystems/WorldSubsystem.h"
#include "SW_BulletManager.generated.h"

class ASW_BulletPoolItem;
/**
 * 用于子弹的对象池
 */
UCLASS()
class SPACEWAR_API USW_BulletManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:

private:
	UPROPERTY()
	TArray<ASW_BulletPoolItem*> BulletFreeList;

	UPROPERTY()
	TArray<ASW_BulletPoolItem*> BulletUsedList;

public:
	/*
	 * 初始化子弹池
	 */
	UFUNCTION(BlueprintCallable)
	void InitBulletPool(const TSubclassOf<ASW_BulletPoolItem> InBulletPoolItemClass, const int32 InPoolSize = 100);

	UPROPERTY()
	TSubclassOf<ASW_BulletPoolItem> BulletPoolItemClass;

	int32 PoolSize;
	/*
	 * 池内没有空闲的子弹,则创建一个
	 */
	UFUNCTION(BlueprintCallable)
	ASW_BulletPoolItem* GetBullet(const FBulletItemParam& InBulletParam);

	/*
	 * 释放子弹,归还子弹,子弹将自动释放
	 */
	void ReturnBullet(ASW_BulletPoolItem* Bullet);


	UFUNCTION(BlueprintCallable)
	int32 GetBulletUsedNum() const { return BulletUsedList.Num(); }

	UFUNCTION(BlueprintCallable)
	int32 GetBulletFreeNum() const { return BulletFreeList.Num(); }
};
