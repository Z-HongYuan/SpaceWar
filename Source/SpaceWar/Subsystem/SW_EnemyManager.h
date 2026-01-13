// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceWar/Data/SW_EnemyType.h"
#include "Subsystems/WorldSubsystem.h"
#include "SW_EnemyManager.generated.h"


/**
 * 用于敌人对象池的管理
 */
UCLASS()
class SPACEWAR_API USW_EnemyManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:
	void InitEnemyPool();

	void GetEnemyFromPool(EEnemyType EnemyType, TObjectPtr<class ASW_Enemy>& OutEnemy);

private:
	/*
	 * 敌人Array
	 */
	UPROPERTY()
	TArray<TObjectPtr<class ASW_Enemy>> EnemyArray;

	/*
	 * 敌人最大数量
	 */
	UPROPERTY()
	TArray<FEnemyPoolParameter> EnemyPoolNum;

public:
};
