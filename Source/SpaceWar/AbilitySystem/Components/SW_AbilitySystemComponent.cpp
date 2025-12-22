// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_AbilitySystemComponent.h"


USW_AbilitySystemComponent::USW_AbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USW_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USW_AbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
