// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StateTreeComponent.h"
#include "GameFramework/Actor.h"
#include "SW_Enemy.generated.h"

class UNiagaraSystem;
class UGameplayEffect;
/*
 * 简单Enemy
 * 有初始血量
 * 只会执行状态树,并且受到伤害
 */
UCLASS()
class SPACEWAR_API ASW_Enemy : public AActor
{
	GENERATED_BODY()

public:
	ASW_Enemy();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                       const FHitResult& SweepResult);

	/*
	 * 因为是使用的设置移动,所以永远不会触发Hit
	 */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(Category=SpaceWar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStateTreeComponent> StateTreeComponent;

	UPROPERTY(Category=SpaceWar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(Category=SpaceWar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

public:
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Enemy")
	float Health;

	/*
	 * 必须使用针对于Pawn造成伤害的GameplayEffect,如果需要伤害削减的话,需要使用MetaDamage属性
	 */
	UPROPERTY(Category=SpaceWar, EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> EffectClass;

	// 被攻击时的特效
	UPROPERTY(Category=SpaceWar, EditDefaultsOnly)
	TSoftObjectPtr<UNiagaraSystem> HitFX;

	// 死亡时的特效
	UPROPERTY(Category=SpaceWar, EditDefaultsOnly)
	TSoftObjectPtr<UNiagaraSystem> DieFX;
};
