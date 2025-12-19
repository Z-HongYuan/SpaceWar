// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CombatPawn.h"


ASW_CombatPawn::ASW_CombatPawn()
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
}
