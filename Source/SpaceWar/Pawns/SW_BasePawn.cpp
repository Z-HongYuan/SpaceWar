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
	GameplayCamera->bAutoActivate = false;
}

void ASW_BasePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PlayerController = Cast<APlayerController>(NewController))
	{
		GameplayCamera->ActivateCameraForPlayerController(PlayerController);
	}
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
