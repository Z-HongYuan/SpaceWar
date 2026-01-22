// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SW_BuildingActor.h"
#include "Components/StateTreeComponent.h"
#include "SW_CombatActor.generated.h"

class USW_PrimaryFogOfWarComp;
class UGameplayAbility;
class UAbilitySystemComponent;
/*
 * 战斗ActorBase
 * 通过GameplayTags判断是否激活状态树
 * 如果Pawn内有ASC,游戏开始就会执行状态树
 */
UCLASS(Abstract)
class SPACEWAR_API ASW_CombatActor : public ASW_BuildingActor
{
	GENERATED_BODY()

public:
	ASW_CombatActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStateTreeComponent> StateTreeComponent;

	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_PrimaryFogOfWarComp> PrimaryFogOfWarComp;

	UPROPERTY(Category="SpaceWar|Ability", EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> AbilityClassArray;

	void AddAbilityToOwner();

	UAbilitySystemComponent* GetOwnerAbilitySystemComponent();

public:
};
