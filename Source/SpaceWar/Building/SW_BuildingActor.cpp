// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_BuildingActor.h"

#include "SpaceWar/FunctionLibrary/SW_BuildingFunction.h"


ASW_BuildingActor::ASW_BuildingActor() :
	BuildingMesh(CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh"))
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(BuildingMesh);
}

void ASW_BuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_BuildingActor::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FIntPoint> ASW_BuildingActor::GetShapeFootPrint()
{
	TArray<FIntPoint> FootPrint = USW_BuildingFunction::BFL_GetShapeFootPrint(BuildingGridType);

	for (int i = 0; i < CurrentRotate / 90; ++i)
	{
		//处理旋转了多少次90度
		USW_BuildingFunction::BFL_RotateFootPrint(FootPrint);
	}

	return FootPrint;
}

void ASW_BuildingActor::SetIsSelected(bool bInSelected)
{
	bIsSelected = bInSelected;
	OnSelectedChange(bIsSelected);
}
