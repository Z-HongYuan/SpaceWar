// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SW_EnemyManager.generated.h"


struct FEnemyItemParam;
class ASW_EnemyPoolItem;
/**
 * 用于敌人对象池的管理
 * 将Hidden作为标志位,所有检测是否存在/生命周期的判断都通过Hidden进行
 */
UCLASS()
class SPACEWAR_API USW_EnemyManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:

private:
	/*
	 * 敌人Array
	 */
	UPROPERTY()
	TArray<ASW_EnemyPoolItem*> EnemyFreeList;

	UPROPERTY()
	TArray<ASW_EnemyPoolItem*> EnemyUsedList;

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyPool(const TSubclassOf<ASW_EnemyPoolItem> InEnemyPoolItemClass, const int32 InPoolSize = 100);

	//对象池内数量
	float PoolSize;

	//要生成的Class
	UPROPERTY()
	TSubclassOf<ASW_EnemyPoolItem> EnemyPoolItemClass;

	UFUNCTION(BlueprintCallable)
	ASW_EnemyPoolItem* GetEnemy(const FEnemyItemParam& InEnemyParam);

	void ReturnEnemy(ASW_EnemyPoolItem* Enemy);

	UFUNCTION(BlueprintCallable)
	int32 GetEnemyUsedNum() const { return EnemyUsedList.Num(); }

	UFUNCTION(BlueprintCallable)
	int32 GetEnemyFreeNum() const { return EnemyFreeList.Num(); }
};
