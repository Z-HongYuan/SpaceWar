// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "SW_SpawnDefaultActor.generated.h"

/**
 * 必定生成一个Actor
 * Owner和Instigator都是Context的拥有者
 */
UCLASS()
class SPACEWAR_API USW_SpawnDefaultActor : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	USW_SpawnDefaultActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
	{
	}

protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

private:

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Context")
	TObjectPtr<AActor> ContextObject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TSubclassOf<AActor> SpawnedClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
	FTransform SpawnTransform;
};
