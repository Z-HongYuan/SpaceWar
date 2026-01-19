// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_MoveToPlayer.h"

#include "Kismet/KismetMathLibrary.h"

EStateTreeRunStatus USW_MoveToPlayer::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	return Super::EnterState(Context, Transition);
}

EStateTreeRunStatus USW_MoveToPlayer::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	RunStatus = Super::Tick(Context, DeltaTime);

	const FVector ContextLocation = ContextObject->GetActorLocation();
	const FVector TargetLocation = TargetObject->GetActorLocation();

	ContextObject->SetActorLocationAndRotation(
		ContextLocation + MoveSpeed * DeltaTime * (TargetLocation - ContextLocation).GetSafeNormal(),
		UKismetMathLibrary::FindLookAtRotation(ContextLocation, TargetLocation),
		true);

	if ((TargetLocation - ContextLocation).SizeSquared2D() <= DistanceRange)
	{
		RunStatus = EStateTreeRunStatus::Succeeded;
	}
	else
	{
		RunStatus = EStateTreeRunStatus::Running;
	}

	return RunStatus;
}
