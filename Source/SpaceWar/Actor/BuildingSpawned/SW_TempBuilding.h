// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceWar/Building/CombatActor/SW_CombatActor.h"
#include "SW_TempBuilding.generated.h"

/*
 * 用于处理建筑装置生成的临时Actor
 * 可能会作为炸弹或者炮台,类似于战斗建筑
 * 临时Actor
 */
UCLASS()
class SPACEWAR_API ASW_TempBuilding : public ASW_CombatActor
{
	GENERATED_BODY()

public:
	ASW_TempBuilding();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:

public:
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "BuildingSpawned")
	bool bIsAttached;
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "BuildingSpawned")
	float ActivationTime;
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "BuildingSpawned")
	float ActivationDelay;
};
