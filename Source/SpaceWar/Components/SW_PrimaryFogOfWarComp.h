// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SW_PrimaryFogOfWarComp.generated.h"

/*
 * 战争迷雾主组件
 * 会Tick设置范围内的Enemy对象可视性
 * 主要是探测
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USW_PrimaryFogOfWarComp : public UActorComponent
{
	GENERATED_BODY()

public:
	USW_PrimaryFogOfWarComp();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FogOfWar")
	float ViewRange = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FogOfWar")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FogOfWar")
	TSubclassOf<AActor> ActorClassFilter;
};
