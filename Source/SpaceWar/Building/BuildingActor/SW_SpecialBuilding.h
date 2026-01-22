// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceWar/Building/SW_BuildingActor.h"
#include "SW_SpecialBuilding.generated.h"

class USW_SpawnCellsComp;

UCLASS(Abstract)
class SPACEWAR_API ASW_SpecialBuilding : public ASW_BuildingActor
{
	GENERATED_BODY()

public:
	ASW_SpecialBuilding();

	virtual void OnBuilded() override;

private:
	UPROPERTY(Category=Building, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_SpawnCellsComp> SpawnCellsComp;
};
