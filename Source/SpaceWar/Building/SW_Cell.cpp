// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Cell.h"


ASW_Cell::ASW_Cell() :
	CellMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh")))
{
	PrimaryActorTick.bCanEverTick = bIsDebug;

	SetRootComponent(CellMesh);
	CellMesh->SetCollisionProfileName(TEXT("Cell"));
	CellMesh->SetGenerateOverlapEvents(false);
}

void ASW_Cell::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red,
	                                 FString::Printf(TEXT("Cell名字 %s \n上面的建筑 %s\n占用状态: %s"),
	                                                 *GetName(),
	                                                 OccupiedActor.IsValid() ? *OccupiedActor->GetName() : TEXT("nullptr"),
	                                                 bIsOccupied ? TEXT("True") : TEXT("False")));
}

void ASW_Cell::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (OccupiedActor.IsValid())
	{
		OccupiedActor->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}

void ASW_Cell::SetCellState(const ECellState& InCellState)
{
	if (CellState == InCellState) return;
	CellState = InCellState;
	OnCellStateChanged(CellState);
}
