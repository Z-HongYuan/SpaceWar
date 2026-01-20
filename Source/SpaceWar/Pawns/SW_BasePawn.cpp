// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BasePawn.h"

#include "GameFramework/GameplayCameraComponent.h"


ASW_BasePawn::ASW_BasePawn() :
	Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"))),
	GameplayCamera(CreateDefaultSubobject<UGameplayCameraComponent>(TEXT("GameplayCamera"))),
	GridBuildComponent(CreateDefaultSubobject<USW_GridBuildComponent>(TEXT("GridBuildComponent")))
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(Mesh);

	GameplayCamera->SetupAttachment(GetRootComponent());
	GameplayCamera->bAutoActivate = false;
	GameplayCamera->bSetControlRotationWhenViewTarget = false; //关闭设置控制旋转,因为需要设置默认旋转
}

void ASW_BasePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PlayerController = Cast<APlayerController>(NewController))
	{
		GameplayCamera->ActivateCameraForPlayerController(PlayerController);
	}
}
