// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_FloatingPawnMovement.h"

#include "AbilitySystemComponent.h"
#include "SpaceWar/AbilitySystem/Attributes/SW_AttributeSetBase.h"
#include "SpaceWar/Pawns/SW_CombatPawn.h"


USW_FloatingPawnMovement::USW_FloatingPawnMovement()
{
	PrimaryComponentTick.bCanEverTick = true;

	//设置平面约束
	bConstrainToPlane = true;
	bSnapToPlaneAtStart = true;
	UMovementComponent::SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);

	//设置基本的移动参数
	MaxSpeed = 0.f;
	Acceleration = 0.f;
	Deceleration = 0.f;
	TurningBoost = 0.f;
}

void USW_FloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USW_FloatingPawnMovement::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UpdateAttributeDelegate(false);

	Super::EndPlay(EndPlayReason);
}

void USW_FloatingPawnMovement::AddInputVector(FVector WorldVector, bool bForce)
{
	/*
	 * To Check Rules
	 * 1. 检查输入方向的40度之内是否存在推进器
	 * 2. 激活推进器
	 * 3. 停用所有不满足条件1的推进器
	 * 4. 筛选/过滤输入向量(未完成),当输入向量为左前时,正后方推进器被激活,移动方向为左前
	 */
	bool bHasPropeller = false;

	if (PropellerArray.Num() == 0)
	{
		Super::AddInputVector(FVector(0, 0, 0), bForce);
	}

	for (ASW_Building_Propeller*& Propeller : PropellerArray)
	{
		double Angle = -WorldVector.Dot(Propeller->Direction);

		//夹角小于40度材激活
		if (Angle > FMath::Cos(FMath::DegreesToRadians(HalfDirectionAngle)))
		{
			Propeller->EnablePropeller();
			bHasPropeller = true;
		}
		else
		{
			Propeller->DisablePropeller();
		}
	}

	//没有对应的推进器,搞个事件给个UI提示
	if ((PropellerArray.Num() == 0 or !bHasPropeller) && !WorldVector.IsNearlyZero())
	{
		OnNoPropeller.Broadcast(bHasPropeller);
	}


	Super::AddInputVector(WorldVector, bForce);
}

void USW_FloatingPawnMovement::BeginPlay()
{
	Super::BeginPlay();

	UpdateAttributeDelegate(true);
}

void USW_FloatingPawnMovement::UpdateAttributeDelegate(bool bIsAdd)
{
	if (bIsAdd)
	{
		//添加属性监听

		UAbilitySystemComponent* ASC = GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent();
		check(ASC);

		/*
		 * 添加MaxSpeed属性监听
		 */
		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetMaxSpeedAttribute()
		).AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
		{
			MaxSpeed = Data.NewValue;
		});

		/*
		 * 添加Acceleration属性监听
		 */
		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetAccelerationAttribute()
		).AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
		{
			Acceleration = Data.NewValue;
		});
	}
	else
	{
		//移除属性监听

		UAbilitySystemComponent* ASC = GetOwner<ASW_CombatPawn>()->GetAbilitySystemComponent();;
		check(ASC);

		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetMaxSpeedAttribute()
		).RemoveAll(this);

		ASC->GetGameplayAttributeValueChangeDelegate(
			USW_AttributeSetBase::GetAccelerationAttribute()
		).RemoveAll(this);
	}
}

void USW_FloatingPawnMovement::UpdatePropellerArray()
{
	PropellerArray.Empty();

	GetOwner<ASW_CombatPawn>()->ForEachAttachedActors([this](AActor* AttachedActor)
	{
		UE_LOG(LogTemp, Log, TEXT("Child: %s"), *AttachedActor->GetName());
		if (AttachedActor->IsA<ASW_Building_Propeller>())
		{
			PropellerArray.Add(Cast<ASW_Building_Propeller>(AttachedActor));
		}
		return true; // 继续
	});
}

void USW_FloatingPawnMovement::AddInputRotation(float InRotation)
{
	if (InRotation > 0) //向右旋转
	{
		GetOwner()->SetActorRotation(FRotator(0, GetOwner()->GetActorRotation().Yaw + 90.f, 0));
	}
	else //向左旋转
	{
		GetOwner()->SetActorRotation(FRotator(0, GetOwner()->GetActorRotation().Yaw - 90.f, 0));
	}

	for (ASW_Building_Propeller*& Propeller : PropellerArray)
	{
		Propeller->UpdateDirection();
	}
}

void USW_FloatingPawnMovement::EmergencyStop(bool InRotation)
{
	if (!GetVelocityForNavMovement().IsNearlyZero(5) and InRotation)
	{
		AddInputVector(-GetVelocityForNavMovement().GetSafeNormal());
	}
	else
	{
		AddInputVector(FVector(0, 0, 0));
	}


	//获取当前速度
}
