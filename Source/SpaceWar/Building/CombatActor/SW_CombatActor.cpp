// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CombatActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "SpaceWar/AbilitySystem/Abilities/SW_AbilityBase.h"
#include "SpaceWar/Components/SW_PrimaryFogOfWarComp.h"
#include "SpaceWar/Data/SW_GameplayTags.h"


ASW_CombatActor::ASW_CombatActor() :
	StateTreeComponent(CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"))),
	PrimaryFogOfWarComp(CreateDefaultSubobject<USW_PrimaryFogOfWarComp>(TEXT("PrimaryFogOfWarComp")))

{
	PrimaryActorTick.bCanEverTick = true;

	StateTreeComponent->SetStartLogicAutomatically(false);
}

void ASW_CombatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_CombatActor::BeginPlay()
{
	Super::BeginPlay();

	//保证状态树在战争迷雾Tick的后面,因为战争迷雾会改变Enemy的Visibility,射击子弹时需要检测可见
	if (StateTreeComponent and PrimaryFogOfWarComp)
		StateTreeComponent->AddTickPrerequisiteComponent(PrimaryFogOfWarComp);

	AddAbilityToOwner();

	if (GetOwnerAbilitySystemComponent() and GetOwnerAbilitySystemComponent()->HasMatchingGameplayTag(TAG_LevelState_Combat))
	{
		// Pawn 拥有该 GameplayTag,执行行为树
		StateTreeComponent->StartLogic();
	}
}

void ASW_CombatActor::AddAbilityToOwner()
{
	if (!GetOwnerAbilitySystemComponent()) return;

	for (const TSubclassOf<UGameplayAbility>& Ability : AbilityClassArray)
	{
		GetOwnerAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0, this));
	}
}

UAbilitySystemComponent* ASW_CombatActor::GetOwnerAbilitySystemComponent()
{
	const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(GetOwner());
	if (!ASI) return nullptr;
	UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
	return ASC ? ASC : nullptr;
}
