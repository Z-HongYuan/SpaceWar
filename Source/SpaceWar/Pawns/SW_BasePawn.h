// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SW_BasePawn.generated.h"

/*
 * 基础Pawn
 * 创建局内局外公有的函数
 */
UCLASS()
class SPACEWAR_API ASW_BasePawn : public APawn
{
	GENERATED_BODY()

public:
	ASW_BasePawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:

public:
};
