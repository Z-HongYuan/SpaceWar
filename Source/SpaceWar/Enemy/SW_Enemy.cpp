// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Enemy.h"


ASW_Enemy::ASW_Enemy() :
	StateTreeComponent(CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent")))
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASW_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_Enemy::BeginPlay()
{
	Super::BeginPlay();
}
