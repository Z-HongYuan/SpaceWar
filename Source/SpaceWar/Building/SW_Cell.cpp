// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Cell.h"


ASW_Cell::ASW_Cell() :
	CellMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh")))
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CellMesh);
}

void ASW_Cell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_Cell::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_Cell::SetCellState(const ECellState& InCellState)
{
	CellState = InCellState;
	OnCellStateChanged(CellState);
}
