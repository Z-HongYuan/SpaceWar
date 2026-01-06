// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_TempBuilding.h"


ASW_TempBuilding::ASW_TempBuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	// InitialLifeSpan = ActivationTime;不会生效,会被蓝图覆盖
}

void ASW_TempBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_TempBuilding::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(ActivationTime);

	if (bIsAttached)
	{
		AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	}
}
