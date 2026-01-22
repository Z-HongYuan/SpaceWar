// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_CombatActor.h"
#include "SW_SpawnedActor.generated.h"

/*
 * 建筑
 * 生成建筑的建筑
 */
UCLASS(Abstract)
class SPACEWAR_API ASW_SpawnedActor : public ASW_CombatActor
{
	GENERATED_BODY()

public:
	ASW_SpawnedActor();

protected:

private:

public:
};
