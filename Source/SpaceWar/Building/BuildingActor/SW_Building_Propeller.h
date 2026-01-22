// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "SpaceWar/Building/SW_BuildingActor.h"
#include "SW_Building_Propeller.generated.h"

class UGameplayEffect;
/*
 * 推进器Actor
 */
UCLASS(Abstract)
class SPACEWAR_API ASW_Building_Propeller : public ASW_BuildingActor
{
	GENERATED_BODY()

public:
	ASW_Building_Propeller();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FActiveGameplayEffectHandle EffectHandle;

	FDelegateHandle OnFuelChangeDelegateHandle;

public:
	void EnablePropeller();

	void DisablePropeller();

	UFUNCTION(BlueprintImplementableEvent, Category = "Propeller")
	void OnPropellerChange(bool bIsEnable);

	//所使用的GE为模版GE
	UPROPERTY(EditDefaultsOnly, Category = "Propeller")
	TSubclassOf<UGameplayEffect> EffectClass;

	//加速度,只有用到了,才会添加
	UPROPERTY(EditDefaultsOnly, Category = "Propeller")
	float Acceleration;

	//燃料消耗,只要用到了就要减少,每秒
	UPROPERTY(EditDefaultsOnly, Category = "Propeller")
	float FuelCost;

	bool bIsEnablePropeller = false;

	//方向坐标
	FVector Direction;

	void UpdateDirection();
};
