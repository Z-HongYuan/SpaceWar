// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_EnemyManager.h"

#include "SpaceWar/Enemy/SW_EnemyPoolItem.h"

bool USW_EnemyManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Outer->GetWorld()->GetMapName().Contains("Combat", ESearchCase::IgnoreCase)) return false;
	return Super::ShouldCreateSubsystem(Outer);
}

void USW_EnemyManager::InitEnemyPool(const TSubclassOf<ASW_EnemyPoolItem> InEnemyPoolItemClass, const int32 InPoolSize)
{
	if (!GetWorld()) return;
	if (!InEnemyPoolItemClass) return;
	EnemyPoolItemClass = InEnemyPoolItemClass;
	PoolSize = InPoolSize;

	const FTransform TempTransform = FTransform();
	for (int32 i = 0; i < PoolSize; i++)
	{
		ASW_EnemyPoolItem* TempBullet = GetWorld()->SpawnActorDeferred<ASW_EnemyPoolItem>(EnemyPoolItemClass, TempTransform, nullptr, nullptr,
		                                                                                  ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		TempBullet->EnemyManager = this;
		TempBullet->FinishSpawning(TempTransform);
		TempBullet->DeactiveItem();
		EnemyFreeList.Add(TempBullet);
	}
}

ASW_EnemyPoolItem* USW_EnemyManager::GetEnemy(const FEnemyItemParam& InEnemyParam)
{
	if (EnemyFreeList.Num() > 0)
	{
		ASW_EnemyPoolItem* TempEnemy = EnemyFreeList.Pop();
		TempEnemy->ActiveItem(InEnemyParam);
		EnemyUsedList.Add(TempEnemy);
		return TempEnemy;
	}

	//新建并返回
	if (!EnemyPoolItemClass) return nullptr;
	ASW_EnemyPoolItem* TempBullet = GetWorld()->SpawnActor<ASW_EnemyPoolItem>(EnemyPoolItemClass);
	TempBullet->EnemyManager = this;
	TempBullet->ActiveItem(InEnemyParam);
	EnemyUsedList.Add(TempBullet);
	return TempBullet;
}

void USW_EnemyManager::ReturnEnemy(ASW_EnemyPoolItem* Enemy)
{
	if (!Enemy) return;
	EnemyUsedList.RemoveSingle(Enemy);
	Enemy->DeactiveItem();
	EnemyFreeList.Add(Enemy);
}
