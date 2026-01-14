// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BulletPoolItem.h"

#include "SpaceWar/Data/SW_PoolType.h"
#include "SpaceWar/Subsystem/SW_BulletManager.h"


ASW_BulletPoolItem::ASW_BulletPoolItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASW_BulletPoolItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_BulletPoolItem::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_BulletPoolItem::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//应用伤害
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	ReturnBullet();
}


void ASW_BulletPoolItem::LifeSpanTimer()
{
	ReturnBullet();
}

void ASW_BulletPoolItem::SetIsUse(bool InIsUse, const FBulletItemParam& InBulletParam)
{
	bIsUse = InIsUse;

	if (InIsUse)
	{
		bIsActiveMovement = true;
		//正在使用
		SetActorEnableCollision(true);
		SetActorHiddenInGame(false);

		/*
		 * 重新设置位置和移动
		 */
		SetBulletParam(InBulletParam);

		/*
		 * 设置生命周期
		 */
		GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &ThisClass::LifeSpanTimer, 5.f, false);
	}
	else
	{
		bIsActiveMovement = false;

		//取消使用
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
		/*
		 * 归位位置,重置移动
		 */
		SetBulletParam(InBulletParam);

		GetWorldTimerManager().ClearTimer(LifeSpanTimerHandle);
	}

	CallByUsed(InIsUse);
}

void ASW_BulletPoolItem::ReturnBullet()
{
	if (!bIsUse) return;
	if (BulletManager.IsValid())
	{
		BulletManager->ReturnBullet(this);
	}
}

void ASW_BulletPoolItem::SetBulletParam(const FBulletItemParam& InBulletParam)
{
	SetOwner(InBulletParam.InNeedOwner);
	SetActorTransform(InBulletParam.InSpawnLocation);
	BallisticVelocity = InBulletParam.BallisticVelocity;
	Damage = InBulletParam.Damage;
	DamageRange = InBulletParam.DamageRange;
	TrackingMode = InBulletParam.TrackingMode;
	TargetActor = InBulletParam.TargetActor;
}
