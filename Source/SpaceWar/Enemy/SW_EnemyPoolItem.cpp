// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_EnemyPoolItem.h"

#include "NiagaraFunctionLibrary.h"
#include "SpaceWar/Components/SW_SecondaryFogOfWarComp.h"
#include "SpaceWar/Data/SW_PoolType.h"
#include "SpaceWar/Subsystem/SW_EnemyManager.h"


class UNiagaraSystem;

ASW_EnemyPoolItem::ASW_EnemyPoolItem() :
	StateTreeComponent(CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"))),
	BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"))),
	StaticMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"))),
	SecondaryFogOfWarComp(CreateDefaultSubobject<USW_SecondaryFogOfWarComp>(TEXT("SecondaryFogOfWarComp")))

{
	PrimaryActorTick.bCanEverTick = true;

	StateTreeComponent->SetStartLogicAutomatically(false);

	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Enemy"));
	BoxComponent->SetGenerateOverlapEvents(false);

	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMeshComponent->bRenderCustomDepth = true;
}

void ASW_EnemyPoolItem::BeginPlay()
{
	Super::BeginPlay();

	//保证状态树在战争迷雾Tick的后面,因为战争迷雾会改变Enemy的Visibility,需要检测可见
	if (StateTreeComponent and SecondaryFogOfWarComp)
		StateTreeComponent->AddTickPrerequisiteComponent(SecondaryFogOfWarComp);
}

void ASW_EnemyPoolItem::ActiveItem(const FEnemyItemParam& InEnemyItemParam)
{
	StaticMeshComponent->SetCustomDepthStencilValue(0);

	Health = InEnemyItemParam.InHealth;

	SetActorTransform(InEnemyItemParam.InSpawnTransform);

	//重新生成后不会显示,将会在战争迷雾组件中处理显示层
	// SetActorHiddenInGame(false);

	SetActorEnableCollision(true);

	StateTreeComponent->RestartLogic();
}

void ASW_EnemyPoolItem::DeactiveItem()
{
	//播放死亡特效||优先于设置位置
	if (Health <= 0.0f)
		if (UNiagaraSystem* FX = DieFX.LoadSynchronous())
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				FX,
				GetActorLocation(),
				GetActorRotation(),
				FVector(1),
				true,
				true,
				ENCPoolMethod::AutoRelease,
				true);

	SetActorTransform(FTransform());

	SetActorHiddenInGame(true);

	SetActorEnableCollision(false);

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
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			FX, GetActorLocation(),
			GetActorRotation(),
			FVector(1),
			true,
			true,
			ENCPoolMethod::AutoRelease,
			true);


	return DamageTaken;
}
