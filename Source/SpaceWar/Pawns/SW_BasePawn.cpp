// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BasePawn.h"

#include "GameFramework/GameplayCameraComponent.h"


ASW_BasePawn::ASW_BasePawn() :
	Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"))),
	GameplayCamera(CreateDefaultSubobject<UGameplayCameraComponent>(TEXT("GameplayCamera")))
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(Mesh);

	GameplayCamera->SetupAttachment(GetRootComponent());
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
