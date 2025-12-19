// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BasePawn.h"


ASW_BasePawn::ASW_BasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASW_BasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_BasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASW_BasePawn::BeginPlay()
{
	Super::BeginPlay();
}
