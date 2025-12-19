// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_BasePawn.h"
#include "SW_CombatPawn.generated.h"

class USW_FloatingPawnMovement;
/*
 * 用于战斗的Pawn
 */
UCLASS()
class SPACEWAR_API ASW_CombatPawn : public ASW_BasePawn
{
	GENERATED_BODY()

public:
	ASW_CombatPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	/*
	 * 基础的漂浮组件
	 */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_FloatingPawnMovement> FloatingMovement;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE USW_FloatingPawnMovement* GetFloatingMovement() const { return FloatingMovement; }
};
