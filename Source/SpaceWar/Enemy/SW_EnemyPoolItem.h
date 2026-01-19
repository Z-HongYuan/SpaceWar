// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StateTreeComponent.h"
#include "GameFramework/Actor.h"
#include "SpaceWar/Interface/SW_CombatInterface.h"
#include "SW_EnemyPoolItem.generated.h"

class USW_SecondaryFogOfWarComp;
struct FEnemyItemParam;
class UNiagaraSystem;
class USW_EnemyManager;

UCLASS()
class SPACEWAR_API ASW_EnemyPoolItem : public AActor, public ISW_CombatInterface
{
	GENERATED_BODY()

public:
	ASW_EnemyPoolItem();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=SpaceWar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStateTreeComponent> StateTreeComponent;

	UPROPERTY(Category=SpaceWar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(Category=SpaceWar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(Category=SpaceWar, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_SecondaryFogOfWarComp> SecondaryFogOfWarComp;

public:
	UPROPERTY()
	TWeakObjectPtr<USW_EnemyManager> EnemyManager = nullptr;

	/*
	 * 变换
	 * 显示隐藏
	 * 碰撞
	 * 状态树
	 * 标签配置(是否需要设置标志位,用GameplayTag)
	 * 如何过滤场景查询,避免未启用的时候都会锁定(移动Manager位置)
	 */
	void ActiveItem(const FEnemyItemParam& InEnemyItemParam);
	void DeactiveItem();

	/*
	 * 处理伤害
	 */
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Enemy")
	float Health = 500;

	// 被攻击时的特效
	UPROPERTY(Category=SpaceWar, EditDefaultsOnly)
	TSoftObjectPtr<UNiagaraSystem> HitFX;

	// 死亡时的特效
	UPROPERTY(Category=SpaceWar, EditDefaultsOnly)
	TSoftObjectPtr<UNiagaraSystem> DieFX;

	//~ ISW_CombatInterface Interface 战斗接口
	virtual void OnLocked() override;
	//~ End ISW_CombatInterface Interface
};
