// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_EnemyManager.h"

#include "SpaceWar/Enemy/SW_Enemy.h"

void USW_EnemyManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USW_EnemyManager::Deinitialize()
{
	Super::Deinitialize();
}

bool USW_EnemyManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Outer->GetWorld()->GetMapName().Contains("Combat", ESearchCase::IgnoreCase)) return false;
	return Super::ShouldCreateSubsystem(Outer);
}

void USW_EnemyManager::InitEnemyPool()
{
	for (FEnemyPoolParameter Element : EnemyPoolNum)
	{
		for (int32 i = 0; i < Element.Num; i++)
		{
			FActorSpawnParameters SpawnParameters;

			GetWorld()->SpawnActor<ASW_Enemy>(Element.EnemyClass, SpawnParameters);
		}
	}
}

void USW_EnemyManager::GetEnemyFromPool(EEnemyType EnemyType, TObjectPtr<class ASW_Enemy>& OutEnemy)
{
}
