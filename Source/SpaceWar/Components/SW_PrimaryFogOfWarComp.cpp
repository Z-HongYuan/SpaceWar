// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PrimaryFogOfWarComp.h"

#include "Kismet/KismetSystemLibrary.h"


USW_PrimaryFogOfWarComp::USW_PrimaryFogOfWarComp()
{
	PrimaryComponentTick.bCanEverTick = true;

	/*
	 * 主要组件将会在渲染前,且次要组件设置后设置敌人的可视性
	 * TickStart->SecondaryComp->PrimaryComp->TickEnd
	 * 意味着主要组件将会覆盖次要组件的设置
	 * 由于Enemy和Player的不对等,所以不能使用前置Tick设置,只能使用TickGroup分类
	 */
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_LastDemotable;
}

void USW_PrimaryFogOfWarComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> EnemyList = {};
	if (UKismetSystemLibrary::SphereOverlapActors(
		GetOwner(),
		GetOwner()->GetActorLocation(),
		ViewRange,
		ObjectTypes,
		ActorClassFilter,
		TArray<AActor*>(),
		EnemyList))
	{
		for (AActor* Enemy : EnemyList)
		{
			Enemy->SetActorHiddenInGame(false);
		}
	}
}

void USW_PrimaryFogOfWarComp::BeginPlay()
{
	Super::BeginPlay();
}
