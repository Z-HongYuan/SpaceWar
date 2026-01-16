// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SecondaryFogOfWarComp.h"


USW_SecondaryFogOfWarComp::USW_SecondaryFogOfWarComp()
{
	PrimaryComponentTick.bCanEverTick = true;

	/*
	 * 次要组件将会在渲染前,主要组件设置前设置不可见
	 * TickStart->SecondaryComp->PrimaryComp->TickEnd
	 * 意味着主要组件将会覆盖次要组件的设置
	 * 由于Enemy和Player的不对等,所以不能使用前置Tick设置,只能使用TickGroup分类
	 */
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

void USW_SecondaryFogOfWarComp::BeginPlay()
{
	Super::BeginPlay();
}

void USW_SecondaryFogOfWarComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//不需要再做判断,UE内部已经节省开销
	GetOwner()->SetActorHiddenInGame(true);
}
