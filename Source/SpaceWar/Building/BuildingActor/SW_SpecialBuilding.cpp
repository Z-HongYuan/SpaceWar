// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SpecialBuilding.h"

#include "SpaceWar/Components/SW_SpawnCellsComp.h"


ASW_SpecialBuilding::ASW_SpecialBuilding() :
	SpawnCellsComp(CreateDefaultSubobject<USW_SpawnCellsComp>(TEXT("SpawnCellsComp")))
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnCellsComp->SetupAttachment(GetRootComponent());
}

void ASW_SpecialBuilding::OnBuilded()
{
	Super::OnBuilded();

	SpawnCellsComp->ChangeCallsCollision(true);
}
