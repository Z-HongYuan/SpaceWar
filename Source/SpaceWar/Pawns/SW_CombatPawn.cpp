// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CombatPawn.h"

#include "SpaceWar/Components/SW_FloatingPawnMovement.h"


ASW_CombatPawn::ASW_CombatPawn() :
	FloatingMovement(CreateDefaultSubobject<USW_FloatingPawnMovement>(TEXT("FloatingMovement")))
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
