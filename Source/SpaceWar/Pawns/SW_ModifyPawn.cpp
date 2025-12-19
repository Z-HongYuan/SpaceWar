// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_ModifyPawn.h"


ASW_ModifyPawn::ASW_ModifyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASW_ModifyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_ModifyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASW_ModifyPawn::BeginPlay()
{
	Super::BeginPlay();
}
