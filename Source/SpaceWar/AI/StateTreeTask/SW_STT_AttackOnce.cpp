// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_STT_AttackOnce.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpaceWar/Interface/SW_CombatInterface.h"
#include "SpaceWar/Subsystem/SW_BulletManager.h"

EStateTreeRunStatus USW_STT_AttackOnce::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	RunStatus = Super::EnterState(Context, Transition);
	if (RunStatus == EStateTreeRunStatus::Failed) return EStateTreeRunStatus::Failed;
	if (!OwnerBuilding and !TargetObject) return EStateTreeRunStatus::Failed;

	//在 Enemy 上 调用锁定事件
	if (ISW_CombatInterface* TempTarget = Cast<ISW_CombatInterface>(TargetObject))
	{
		TempTarget->OnLocked();
	}

	if (bUseAbility)
	{
		//只有建筑的拥有者才拥有ASC
		if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerBuilding->GetOwner()))
		{
			ASC->TryActivateAbilityByClass(AbilityToActivate) ? RunStatus = EStateTreeRunStatus::Succeeded : RunStatus = EStateTreeRunStatus::Failed;
		}
	}
	else
	{
		if (TargetObject->IsHidden()) //如果处于隐藏模式就不会发射子弹,主要由子弹池或者战争迷雾来设置
			return EStateTreeRunStatus::Failed;

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerBuilding->GetActorLocation(), TargetObject->GetActorLocation());
		OwnerBuilding->SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));

		FBulletItemParam BulletItemParam;
		BulletItemParam.InNeedOwner = OwnerBuilding->GetOwner(); //这里可能需要战斗建筑,也可能需要战斗Pawn
		FTransform SpawnTransform = FTransform(LookAtRotation, OwnerBuilding->GetActorLocation());
		BulletItemParam.InSpawnTransform = SpawnTransform;
		BulletItemParam.BallisticVelocity = BallisticVelocity;
		BulletItemParam.DamageRange = DamageRange;
		BulletItemParam.Damage = Damage;
		BulletItemParam.TrackingMode = bTrackingMode;
		BulletItemParam.TargetActor = TargetObject;

		GetWorld()->GetSubsystem<USW_BulletManager>()->GetBullet(BulletItemParam);

		RunStatus = EStateTreeRunStatus::Succeeded;
	}


	return RunStatus;
}
