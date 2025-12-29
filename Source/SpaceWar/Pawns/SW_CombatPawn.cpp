// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CombatPawn.h"

#include "SpaceWar/Components/SW_FloatingPawnMovement.h"


ASW_CombatPawn::ASW_CombatPawn() :
	FloatingMovement(CreateDefaultSubobject<USW_FloatingPawnMovement>(TEXT("FloatingMovement"))),
	AbilitySystemComponent(CreateDefaultSubobject<USW_AbilitySystemComponent>(TEXT("AbilitySystemComponent"))),
	AttributeSet(CreateDefaultSubobject<USW_AttributeSetBase>(TEXT("AttributeSet")))
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASW_CombatPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_CombatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASW_CombatPawn::BeginPlay()
{
	Super::BeginPlay();

	InitAttribute();
}

void ASW_CombatPawn::InitAttribute()
{
	if (GetAbilitySystemComponent() and AttributeSet and DefaultAttributeEffect)
	{
		FGameplayEffectSpecHandle DefaultAtt = GetAbilitySystemComponent()->MakeOutgoingSpec(
			DefaultAttributeEffect,
			1,
			GetAbilitySystemComponent()->MakeEffectContext());
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*DefaultAtt.Data.Get());
	}
}

UAbilitySystemComponent* ASW_CombatPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
