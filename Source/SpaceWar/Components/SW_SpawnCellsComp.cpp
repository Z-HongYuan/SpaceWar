// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SpawnCellsComp.h"

#include "SpaceWar/Building/SW_Cell.h"
#include "SpaceWar/Data/SW_BuildingType.h"


USW_SpawnCellsComp::USW_SpawnCellsComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USW_SpawnCellsComp::BeginPlay()
{
	Super::BeginPlay();
	InitCells();
	ChangeCallsCollision(false);
}

void USW_SpawnCellsComp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//仅在建筑Level使用
	for (ASW_Cell*& Cell : Cells)
	{
		Cell->Destroy();
	}

	Super::EndPlay(EndPlayReason);
}

void USW_SpawnCellsComp::InitCells()
{
	for (const FSpawnCellParam& CellParam : CellsParams)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetOwner<APawn>();
		ASW_Cell* Cell = GetWorld()->SpawnActor<ASW_Cell>(CellClass, CellParam.CellLocation, FRotator::ZeroRotator, SpawnParams);
		Cell->SetAllowTags(CellParam.CellTags);
		Cells.AddUnique(Cell);
		Cell->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void USW_SpawnCellsComp::ChangeCallsCollision(const bool bInCollision)
{
	for (ASW_Cell*& Cell : Cells)
	{
		Cell->SetActorEnableCollision(bInCollision);
	}
}
