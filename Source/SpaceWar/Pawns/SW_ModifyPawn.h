// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_BasePawn.h"
#include "SW_ModifyPawn.generated.h"

/*
 * 用于局外修改的Pawn
 */
UCLASS()
class SPACEWAR_API ASW_ModifyPawn : public ASW_BasePawn
{
	GENERATED_BODY()

public:
	ASW_ModifyPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:

public:
};
