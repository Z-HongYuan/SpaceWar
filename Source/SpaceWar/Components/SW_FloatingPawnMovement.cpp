// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_FloatingPawnMovement.h"

#include "AbilitySystemComponent.h"
#include "SpaceWar/AbilitySystem/Attributes/SW_AttributeSetBase.h"
#include "SpaceWar/Pawns/SW_CombatPawn.h"


USW_FloatingPawnMovement::USW_FloatingPawnMovement()
{
	PrimaryComponentTick.bCanEverTick = true;

	//设置平面约束
	bConstrainToPlane = true;
	bSnapToPlaneAtStart = true;
	UMovementComponent::SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);

	//设置基本的移动参数
	MaxSpeed = 1200.f;
	Acceleration = 200.f;
	Deceleration = 100.f;
	TurningBoost = 0.f;
}

void USW_FloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USW_FloatingPawnMovement::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UpdateAttributeDelegate(false);

	Super::EndPlay(EndPlayReason);
}

void USW_FloatingPawnMovement::AddInputVector(FVector WorldVector, bool bForce)
{
	/*
	 * To Check Rules
	 */


	Super::AddInputVector(WorldVector, bForce);
}

void USW_FloatingPawnMovement::BeginPlay()
{
	Super::BeginPlay();

	UpdateAttributeDelegate(true);
}

void USW_FloatingPawnMovement::UpdateAttributeDelegate(bool bIsAdd)
{
	if (bIsAdd)
	{
		//添加属性监听

		UAbilitySystemComponent* ASC = GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent();
		check(ASC);

		/*
		 * 添加MaxSpeed属性监听
		 */
		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetMaxSpeedAttribute()
		).AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
		{
			MaxSpeed = Data.NewValue;
		});

		/*
		 * 添加Acceleration属性监听
		 */
		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetAccelerationAttribute()
		).AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
		{
			Acceleration = Data.NewValue;
		});
	}
	else
	{
		//移除属性监听

		UAbilitySystemComponent* ASC = GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent();;
		check(ASC);

		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetMaxSpeedAttribute()
		).RemoveAll(this);

		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetAccelerationAttribute()
		).RemoveAll(this);
	}
}
