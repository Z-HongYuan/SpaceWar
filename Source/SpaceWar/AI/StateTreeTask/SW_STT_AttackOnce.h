// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "SW_STT_AttackOnce.generated.h"

class UGameplayAbility;
/**
 * 攻击一次
 * 使用池化子弹进行攻击
 */
UCLASS(meta = (DisplayName = "SW 技能/池化单次攻击"))
class SPACEWAR_API USW_STT_AttackOnce : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:

protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:

public:
	/*
	 * 一般调用者为战斗建筑(CombatBuilding)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Context")
	TObjectPtr<AActor> OwnerBuilding;

	/*
	 * 一般是攻击指向的对象
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<AActor> TargetObject;

	/*
	 * 是否使用技能激活,默认为使用池化子弹
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter|Ability")
	bool bUseAbility = false;

	/*
	 * 附带激活的技能
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter|Ability")
	TSubclassOf<UGameplayAbility> AbilityToActivate;

	/*
	 * 子弹的参数
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
	float BallisticVelocity = 1500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
	float DamageRange = 300.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
	float Damage = 50.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
	bool bTrackingMode = false;
};
