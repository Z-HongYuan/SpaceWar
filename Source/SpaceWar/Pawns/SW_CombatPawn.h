// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "SW_BasePawn.h"
#include "SpaceWar/AbilitySystem/Attributes/SW_AttributeSetBase.h"
#include "SpaceWar/AbilitySystem/Components/SW_AbilitySystemComponent.h"
#include "SW_CombatPawn.generated.h"

class USW_FloatingPawnMovement;
/*
 * 用于战斗的Pawn
 */
UCLASS()
class SPACEWAR_API ASW_CombatPawn : public ASW_BasePawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASW_CombatPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void InitAttribute();

	void InitAbilitySystem();

private:
	/*
	 * 基础的漂浮组件
	 */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_FloatingPawnMovement> FloatingMovement;

	/*
	 * 能力组件
	 */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_AttributeSetBase> AttributeSet;

	UPROPERTY(Category=Pawn, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(Category=Pawn, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayEffect>> StartedEffect;

	UPROPERTY(Category=Pawn, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> StartedAbility;

	/*
	 * 战争迷雾
	 */
	UPROPERTY(Category="Pawn|战争迷雾", EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialParameterCollection> MaterialParameterCollection;

	UPROPERTY(Category="Pawn|战争迷雾", EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	FName ParameterName;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE USW_AttributeSetBase* GetAttributeSet() const { return AttributeSet; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE USW_FloatingPawnMovement* GetFloatingMovement() const { return FloatingMovement; }
};
