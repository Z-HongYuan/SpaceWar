// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SpawnedActor.h"


ASW_SpawnedActor::ASW_SpawnedActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASW_SpawnedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_SpawnedActor::BeginPlay()
{
	Super::BeginPlay();
}
