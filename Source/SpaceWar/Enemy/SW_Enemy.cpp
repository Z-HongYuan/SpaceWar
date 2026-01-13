// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Enemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"


ASW_Enemy::ASW_Enemy() :
	StateTreeComponent(CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"))),
	BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"))),
	StaticMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"))),
	Health(100.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Enemy"));

	StaticMeshComponent->SetupAttachment(BoxComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void ASW_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_Enemy::BeginDestroy()
{
	Super::BeginDestroy();
}

void ASW_Enemy::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxOverlapBegin);
	BoxComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void ASW_Enemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnBoxOverlapBegin);
	BoxComponent->OnComponentHit.RemoveDynamic(this, &ThisClass::OnHit);
	//生成死亡特效
	if (UNiagaraSystem* FX = DieFX.LoadSynchronous())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FX, GetActorLocation(), GetActorRotation());
	}

	Super::EndPlay(EndPlayReason);
}

void ASW_Enemy::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1, FGameplayEffectContextHandle());
		ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);

		Destroy();
	}
}

void ASW_Enemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1, FGameplayEffectContextHandle());
		ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);

		Destroy();
	}
}

float ASW_Enemy::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageTaken > 0.0f)
	{
		Health -= DamageTaken;
		if (Health <= 0.0f)
		{
			Destroy();
		}
	}

	//生成受击粒子特效
	if (UNiagaraSystem* FX = HitFX.LoadSynchronous())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FX, GetActorLocation(), GetActorRotation());
	}

	return DamageTaken;
}
