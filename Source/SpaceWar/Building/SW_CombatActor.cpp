// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CombatActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "SpaceWar/Data/SW_GameplayTags.h"


ASW_CombatActor::ASW_CombatActor() :
	StateTreeComponent(CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	StateTreeComponent->SetStartLogicAutomatically(false);
}

void ASW_CombatActor::BeginPlay()
{
	Super::BeginPlay();

	APawn* Pawn = GetOwner<APawn>();

	if (Pawn && Pawn->Implements<UAbilitySystemInterface>())
	{
		UAbilitySystemComponent* ASC = Cast<IAbilitySystemInterface>(Pawn)->GetAbilitySystemComponent();

		if (ASC && ASC->HasMatchingGameplayTag(TAG_LevelState_Combat))
		{
			// Pawn 拥有该 GameplayTag,执行行为树
			StateTreeComponent->StartLogic();
		}
	}
}

void ASW_CombatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
