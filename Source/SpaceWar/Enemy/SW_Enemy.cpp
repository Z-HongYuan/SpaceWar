// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Enemy.h"


ASW_Enemy::ASW_Enemy() :
	StateTreeComponent(CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"))),
	Health(100.0f)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASW_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

float ASW_Enemy::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	auto DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageTaken > 0.0f)
	{
		Health -= DamageTaken;
		if (Health <= 0.0f)
		{
			Destroy();
		}
	}
	return DamageTaken;
}
