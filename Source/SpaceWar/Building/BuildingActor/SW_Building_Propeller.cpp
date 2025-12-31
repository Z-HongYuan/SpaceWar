// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Building_Propeller.h"

#include "SpaceWar/Data/SW_GameplayTags.h"
#include "SpaceWar/Pawns/SW_CombatPawn.h"


class ASW_CombatPawn;

ASW_Building_Propeller::ASW_Building_Propeller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASW_Building_Propeller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_Building_Propeller::UpdateDirection()
{
	Direction = (GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
}

void ASW_Building_Propeller::BeginPlay()
{
	Super::BeginPlay();

	UpdateDirection();
}

void ASW_Building_Propeller::EnablePropeller()
{
	//应用消耗和加速度
	// Acceleration 通过GE添加到Acceleration
	// FuelCost 通过GE添加到FuelCost

	//如果启动就不需要再启动了
	if (bIsEnablePropeller) return;

	const ASW_CombatPawn* CombatPawn = GetOwner<ASW_CombatPawn>();
	if (!CombatPawn) return;

	//检查燃料,持续停止和启动停止
	//1. 启动停止
	const float Fuel = CombatPawn->GetAttributeSet()->GetFuel();
	if (Fuel <= 0 or Fuel < FuelCost) //其实这里检测应该是所有的FuelCost,但是这样也够了
	{
		DisablePropeller();
		return;
	}

	//把设定值设置到GE
	FGameplayEffectSpecHandle EffectSpec = CombatPawn->GetAbilitySystemComponent()->MakeOutgoingSpec(
		EffectClass,
		1,
		CombatPawn->GetAbilitySystemComponent()->MakeEffectContext()
	);
	EffectSpec.Data->SetSetByCallerMagnitude(TAG_DataTag_Acceleration, Acceleration);
	EffectSpec.Data->SetSetByCallerMagnitude(TAG_DataTag_FuelCost, FuelCost);

	EffectHandle = CombatPawn->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(
		*EffectSpec.Data.Get()
	);

	//2. 持续停止. 添加属性监控
	OnFuelChangeDelegateHandle = CombatPawn->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(
		USW_AttributeSetBase::GetFuelAttribute()
	).AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
	{
		if (Data.NewValue <= 0)
		{
			DisablePropeller();
		}
	});

	//触发蓝图事件
	OnPropellerChange(true);

	bIsEnablePropeller = true;
}

void ASW_Building_Propeller::DisablePropeller()
{
	const ASW_CombatPawn* CombatPawn = GetOwner<ASW_CombatPawn>();
	if (!CombatPawn) return;

	//移除消耗和加速度的GE
	if (EffectHandle.IsValid())
	{
		CombatPawn->GetAbilitySystemComponent()->RemoveActiveGameplayEffect(EffectHandle);
	}

	if (OnFuelChangeDelegateHandle.IsValid())
	{
		CombatPawn->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetMaxFuelAttribute()
		).Remove(OnFuelChangeDelegateHandle);
	}

	//触发蓝图事件
	OnPropellerChange(false);

	bIsEnablePropeller = false;
}
