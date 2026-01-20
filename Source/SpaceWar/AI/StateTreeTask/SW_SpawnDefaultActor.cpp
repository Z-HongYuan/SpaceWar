// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SpawnDefaultActor.h"

EStateTreeRunStatus USW_SpawnDefaultActor::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	RunStatus = Super::EnterState(Context, Transition);
	if (RunStatus == EStateTreeRunStatus::Failed) return RunStatus;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = ContextObject->GetOwner();
	SpawnParams.Instigator = Cast<APawn>(ContextObject->GetOwner());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ContextObject->GetWorld()->SpawnActor<AActor>(
		SpawnedClass,
		SpawnTransform,
		SpawnParams
	);

	return EStateTreeRunStatus::Succeeded;
}
