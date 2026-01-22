// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_Bullet.h"
#include "SW_BulletPoolItem.generated.h"

class USW_BulletManager;
struct FBulletItemParam;
/*
 * 用于对象池的子弹对象
 */
UCLASS(Abstract)
class SPACEWAR_API ASW_BulletPoolItem : public ASW_Bullet
{
	GENERATED_BODY()

public:
	ASW_BulletPoolItem();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	UPROPERTY()
	bool bIsUse = false;

	UPROPERTY()
	TWeakObjectPtr<USW_BulletManager> BulletManager;

	FTimerHandle LifeSpanTimerHandle;

	void LifeSpanTimer();
	/*
	 * 设置使用状态
	 * 设置碰撞
	 * 设置位置
	 * 设置显隐
	 * 设置生命周期
	 * 设置Tick
	 */
	void SetIsUse(bool InIsUse, const FBulletItemParam& InBulletParam);
	void ReturnBullet();
	void SetBulletParam(const FBulletItemParam& InBulletParam);
	UFUNCTION(BlueprintImplementableEvent)
	void CallByUsed(bool InIsUse);
};
