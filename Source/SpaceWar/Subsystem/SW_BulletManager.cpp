// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BulletManager.h"

#include "SpaceWar/Actor/Bullet/SW_BulletPoolItem.h"


bool USW_BulletManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Outer->GetWorld()->GetMapName().Contains("Combat", ESearchCase::IgnoreCase)) return false;
	return Super::ShouldCreateSubsystem(Outer);
}

void USW_BulletManager::InitBulletPool()
{
	if (!GetWorld()) return;
	if (!BulletPoolItemClass) return;

	const FTransform TempTransform = FTransform();
	for (int32 i = 0; i < PoolSize; i++)
	{
		ASW_BulletPoolItem* TempBullet = GetWorld()->SpawnActorDeferred<ASW_BulletPoolItem>(BulletPoolItemClass, TempTransform, nullptr, nullptr,
		                                                                                    ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		TempBullet->BulletManager = this;
		TempBullet->FinishSpawning(TempTransform);
		TempBullet->SetIsUse(false, FBulletItemParam());
		BulletFreeList.Add(TempBullet);
	}
}

ASW_BulletPoolItem* USW_BulletManager::GetBullet(const FBulletItemParam& InBulletParam)
{
	if (!InBulletParam.InNeedOwner) return nullptr;

	//如果池内有空闲的子弹
	if (BulletFreeList.Num() > 0)
	{
		ASW_BulletPoolItem* Bullet = BulletFreeList.Pop();
		Bullet->SetIsUse(true, InBulletParam);
		BulletUsedList.Add(Bullet);
		return Bullet;
	}

	if (!BulletPoolItemClass) return nullptr;
	//池内没有空闲的子弹,则创建一个
	ASW_BulletPoolItem* TempBullet = GetWorld()->SpawnActor<ASW_BulletPoolItem>(BulletPoolItemClass);
	TempBullet->BulletManager = this;
	TempBullet->SetIsUse(true, InBulletParam);
	BulletUsedList.Add(TempBullet);

	return TempBullet;
}

void USW_BulletManager::ReturnBullet(ASW_BulletPoolItem* Bullet)
{
	if (!Bullet) return;

	BulletUsedList.RemoveSingle(Bullet);

	Bullet->SetIsUse(false, FBulletItemParam());

	BulletFreeList.Add(Bullet);
}
