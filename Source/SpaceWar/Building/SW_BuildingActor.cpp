// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BuildingActor.h"

#include "SpaceWar/FunctionLibrary/SW_BuildingFunction.h"


ASW_BuildingActor::ASW_BuildingActor() :
	BuildingMesh(CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh"))
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(BuildingMesh);
	BuildingMesh->SetCollisionProfileName(TEXT("Building"));
}

TArray<FIntPoint> ASW_BuildingActor::GetShapeFootPrint()
{
	TArray<FIntPoint> FootPrint = USW_BuildingFunction::BFL_GetShapeFootPrint(BuildingGridType);
	USW_BuildingFunction::BFL_RotatedFootPrint(FootPrint, CurrentRotate);
	return FootPrint;
}

void ASW_BuildingActor::OnBuilded()
{
	K2_OnBuilded();
}

void ASW_BuildingActor::SetIsSelected(bool bInSelected)
{
	if (bIsSelected == bInSelected) return;
	bIsSelected = bInSelected;
	OnSelectedChange(bIsSelected);
}
