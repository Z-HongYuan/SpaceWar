// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_BasePawn.h"
#include "SW_CombatPawn.generated.h"

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

public:
};
