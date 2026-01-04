// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_BuildingActor.h"
#include "Components/StateTreeComponent.h"
#include "SW_CombatActor.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
/*
 * 战斗Actor
 * 通过GameplayTags判断是否激活状态树
 * 如果Pawn内有ASC,游戏开始就会执行状态树
 */
UCLASS()
class SPACEWAR_API ASW_CombatActor : public ASW_BuildingActor
{
	GENERATED_BODY()

public:
	ASW_CombatActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStateTreeComponent> StateTreeComponent;

	UPROPERTY(Category=Ability, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> AbilityClassArray;

	UFUNCTION()
	void AddAbilityToOwner();

	UFUNCTION()
	UAbilitySystemComponent* GetOwnerAbilitySystemComponent();

public:
};
