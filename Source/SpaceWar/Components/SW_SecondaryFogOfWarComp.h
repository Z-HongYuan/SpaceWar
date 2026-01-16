// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SW_SecondaryFogOfWarComp.generated.h"

/*
 * 战争迷雾次组件
 * 用于Enemy身上,为Tick执行的设置不可见
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USW_SecondaryFogOfWarComp : public UActorComponent
{
	GENERATED_BODY()

public:
	USW_SecondaryFogOfWarComp();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:

public:
};
