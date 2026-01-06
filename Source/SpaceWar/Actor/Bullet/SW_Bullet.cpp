// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Bullet.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceWar/Data/SW_CollisionChannels.h"


ASW_Bullet::ASW_Bullet() :
	ProjectileMovement(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"))),
	NiagaraSystem(CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"))),
	BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bUpdateOnlyIfRendered = true;

	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Projectile"));

	SetActorTickInterval(0.5f);

	NiagaraSystem->SetupAttachment(RootComponent);
}

void ASW_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TrackingMode and TargetActor.IsValid())
	//追踪Target,考虑是否在Building中保存当前TargetActor,否则子弹会丢失目标,在目标死亡后
	{
		FVector CurrentVelocity = ProjectileMovement->Velocity;
		FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
		ProjectileMovement->Velocity = Direction.GetSafeNormal() * CurrentVelocity.Size();
	}
	if (!TargetActor.IsValid())
	{
		//判断到底需不需要销毁
		// Destroy();
	}
}

void ASW_Bullet::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovement->Velocity = GetActorRotation().Vector() * BallisticVelocity;;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
}

void ASW_Bullet::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnOverlapBegin);

	Super::EndPlay(EndPlayReason);
}

void ASW_Bullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	//判断DamageRange是否大于0
	if (DamageRange > 0.f)
	{
		//范围伤害
		UGameplayStatics::ApplyRadialDamage(
			GetWorld(),
			Damage,
			GetActorLocation(),
			DamageRange,
			nullptr,
			TArray<AActor*>({this}),
			GetOwner(),
			GetOwner()->GetInstigatorController(),
			true,
			ECC_Trace_Enemy);
	}
	else
	{
		//单体伤害
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			GetOwner()->GetInstigatorController(),
			this,
			nullptr);
	}

	Destroy();
}
