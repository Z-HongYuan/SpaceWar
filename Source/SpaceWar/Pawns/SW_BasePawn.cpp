// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BasePawn.h"

#include "GameFramework/GameplayCameraComponent.h"
#include "SpaceWar/Components/SW_SpawnCellsComp.h"
#include "SpaceWar/FunctionLibrary/SW_CommonFunction.h"
#include "SpaceWar/SaveGame/SW_SaveGame.h"


ASW_BasePawn::ASW_BasePawn() :
	Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"))),
	GameplayCamera(CreateDefaultSubobject<UGameplayCameraComponent>(TEXT("GameplayCamera"))),
	GridBuildComponent(CreateDefaultSubobject<USW_GridBuildComponent>(TEXT("GridBuildComponent"))),
	SpawnCellsComp(CreateDefaultSubobject<USW_SpawnCellsComp>(TEXT("SpawnCellsComp")))
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(Mesh);

	GameplayCamera->SetupAttachment(GetRootComponent());
	GameplayCamera->bAutoActivate = false;
	GameplayCamera->bSetControlRotationWhenViewTarget = false; //关闭设置控制旋转,因为需要设置默认旋转

	SpawnCellsComp->SetupAttachment(GetRootComponent());
}

void ASW_BasePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PlayerController = Cast<APlayerController>(NewController))
		GameplayCamera->ActivateCameraForPlayerController(PlayerController);
}

void ASW_BasePawn::BeginPlay()
{
	Super::BeginPlay();

	//启用Player身上的Cell碰撞
	SpawnCellsComp->ChangeCallsCollision(true);

	//当游戏开始后,都会重建自己的建筑
	if (USW_SaveGame* SaveGame = Cast<USW_SaveGame>(USW_CommonFunction::BFL_GetSaveGameObject(TEXT("Default"), 0, USW_SaveGame::StaticClass())))
	{
		SaveGame->ReBuildActorFromSaveGame(this);
	}
}
