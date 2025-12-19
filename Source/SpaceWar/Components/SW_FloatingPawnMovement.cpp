// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_FloatingPawnMovement.h"


USW_FloatingPawnMovement::USW_FloatingPawnMovement()
{
	PrimaryComponentTick.bCanEverTick = true;

	//设置平面约束
	bConstrainToPlane = true;
	bSnapToPlaneAtStart = true;
	UMovementComponent::SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
}

void USW_FloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USW_FloatingPawnMovement::BeginPlay()
{
	Super::BeginPlay();
}
