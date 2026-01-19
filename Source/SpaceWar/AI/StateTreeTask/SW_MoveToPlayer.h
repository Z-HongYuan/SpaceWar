// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "SW_MoveToPlayer.generated.h"

/**
 * 朝向Player进行移动
 */
UCLASS(meta = (DisplayName = "SW 向Player移动"))
class SPACEWAR_API USW_MoveToPlayer : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	USW_MoveToPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
	{
		bShouldCallTick = true; //启用Tick
	}

protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

private:
public:
	/*
	 * 一般调用者为Enemy
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Context")
	TObjectPtr<AActor> ContextObject;

	/*
	 * 一般是玩家
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<AActor> TargetObject;

	/*
	 * 参数
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
	float MoveSpeed = 300.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Parameter")
	float DistanceRange = 200.0f;
};
