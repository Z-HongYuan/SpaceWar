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

	FGameplayEffectSpecHandle EffectSpec = GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent()->MakeOutgoingSpec(
		EffectClass,
		1,
		GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent()->MakeEffectContext()
	);
	EffectSpec.Data->SetSetByCallerMagnitude(TAG_DataTag_Acceleration, Acceleration);
	EffectSpec.Data->SetSetByCallerMagnitude(TAG_DataTag_FuelCost, FuelCost);

	EffectHandle = GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(
		*EffectSpec.Data.Get()
	);

	OnPropellerChange(true);

	bIsEnablePropeller = true;
}

void ASW_Building_Propeller::DisablePropeller()
{
	//移除消耗和加速度
	if (EffectHandle.IsValid())
	{
		GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent()->RemoveActiveGameplayEffect(EffectHandle);
	}

	bIsEnablePropeller = false;
	OnPropellerChange(false);
}
