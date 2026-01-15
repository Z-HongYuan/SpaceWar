// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_Bullet.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceWar/Data/SW_CollisionChannels.h"


ASW_Bullet::ASW_Bullet() :
	NiagaraSystem(CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"))),
	BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Projectile"));
	BoxComponent->SetGenerateOverlapEvents(false);

	NiagaraSystem->SetupAttachment(RootComponent);
}

void ASW_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickMovement(DeltaTime);
}

void ASW_Bullet::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_Bullet::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASW_Bullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
			ECC_Trace_CanDamage); //使用Enemy通道检测范围Actor
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
}

void ASW_Bullet::TickMovement(float DeltaTime)
{
	if (!bIsActiveMovement) return;

	// ----------------------- 计算本帧位移 -----------------------
	float MoveDistanceThisFrame = BallisticVelocity * DeltaTime;
	FVector DeltaMove = GetActorForwardVector() * MoveDistanceThisFrame; //可以修改位移方向

	// ----------------------- Sweep 检测 -----------------------
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 忽略自己
	QueryParams.AddIgnoredActor(GetOwner()); // 通常忽略发射者
	// QueryParams.bTraceComplex = true;              // 如需精确碰撞可开启（性能代价）

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(), // 起点
		GetActorLocation() + DeltaMove, // 终点
		FQuat::Identity, // 旋转（Box一般不用转）
		ECC_Object_Projectile, // 建议新建一个专用的 Projectile Channel
		FCollisionShape::MakeBox(BoxComponent->GetScaledBoxExtent()), // 用你的 Box 大小
		QueryParams
	);

	if (bHit)
	{
		// 撞到了！手动模拟 Hit 事件
		OnHit(
			BoxComponent,
			HitResult.GetActor(),
			HitResult.GetComponent(),
			FVector::ZeroVector, // 或者用 HitResult.ImpactNormal * someImpulse
			HitResult
		);
	}
	else
	{
		// 没撞到，安全移动
		AddActorWorldOffset(DeltaMove, true); // true = sweep，但我们已经自己扫过了，所以可以 false 省一点性能
	}

	// 可选：更新朝向跟随速度方向（类似 ProjectileMovement 的 bRotationFollowsVelocity）
	if (!DeltaMove.IsNearlyZero())
	{
		SetActorRotation(DeltaMove.Rotation());
	}
}
