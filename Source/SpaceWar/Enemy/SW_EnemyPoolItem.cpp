// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_EnemyPoolItem.h"

#include "NiagaraFunctionLibrary.h"
#include "SpaceWar/Data/SW_PoolType.h"
#include "SpaceWar/Subsystem/SW_EnemyManager.h"


class UNiagaraSystem;

ASW_EnemyPoolItem::ASW_EnemyPoolItem() :
	StateTreeComponent(CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"))),
	BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"))),
	StaticMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	StateTreeComponent->SetStartLogicAutomatically(false);

	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Enemy"));
	BoxComponent->SetGenerateOverlapEvents(false);

	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void ASW_EnemyPoolItem::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_EnemyPoolItem::ActiveItem(const FEnemyItemParam& InEnemyItemParam)
{
	Health = InEnemyItemParam.InHealth;
	SetActorTransform(InEnemyItemParam.InSpawnTransform);
	SetActorHiddenInGame(false);

	SetActorEnableCollision(true);
	BoxComponent->SetCollisionProfileName(TEXT("Enemy"));

	StateTreeComponent->RestartLogic();
}

void ASW_EnemyPoolItem::DeactiveItem()
{
	//播放死亡特效||优先于设置位置
	if (Health <= 0.0f)
		if (UNiagaraSystem* FX = DieFX.LoadSynchronous())
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FX, GetActorLocation(), GetActorRotation());

	SetActorTransform(FTransform());
	SetActorHiddenInGame(true);

	SetActorEnableCollision(false);
	BoxComponent->SetCollisionProfileName(TEXT("NoCollision"));

	StateTreeComponent->StopLogic(TEXT("Deactive"));
}

float ASW_EnemyPoolItem::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageTaken > 0.0f)
	{
		Health -= DamageTaken;
		if (Health <= 0.0f)
		{
			EnemyManager->ReturnEnemy(this);
		}
	}

	//生成受击粒子特效
	if (UNiagaraSystem* FX = HitFX.LoadSynchronous())
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FX, GetActorLocation(), GetActorRotation());


	return DamageTaken;
}
