// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SW_Bullet.generated.h"

/*
 * 作为战斗建筑的子弹
 * 1. 弹道速度
 * 2. 伤害范围
 * 3. 攻击伤害
 * 4. 命中效果
 * 5. 追踪模式
 */
UCLASS()
class SPACEWAR_API ASW_Bullet : public AActor
{
	GENERATED_BODY()

public:
	ASW_Bullet();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void TickMovement(float DeltaTime);

private:
	//Niagara粒子系统
	UPROPERTY(Category = "Projectile", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> NiagaraSystem;

	UPROPERTY(Category = "Projectile", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

public:
	UBoxComponent* GetBoxComponent() const { return BoxComponent; }

	bool bIsActiveMovement = false;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Projectile")
	float BallisticVelocity;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Projectile")
	float DamageRange;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Projectile")
	float Damage;

	/*UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Projectile")
	bool 命中效果;未知*/

	//true:追踪模式,false:直线模式
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Projectile")
	bool TrackingMode;
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Projectile")
	TWeakObjectPtr<AActor> TargetActor;
};
