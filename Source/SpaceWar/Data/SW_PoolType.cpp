// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PoolType.h"

FBulletItemParam::FBulletItemParam()
{
	InNeedOwner = nullptr;
	InSpawnTransform = FTransform();
	BallisticVelocity = 0.f;
	DamageRange = 0.f;
	Damage = 0.f;
	TrackingMode = false;
	TargetActor = nullptr;
}

FBulletItemParam::FBulletItemParam(AActor* InNeedOwner, const FTransform& InSpawnTransform, const float InBallisticVelocity, const float InDamageRange, const float InDamage,
                                   const bool InTrackingMode, AActor* InTargetActor)
{
	this->InNeedOwner = InNeedOwner;
	this->InSpawnTransform = InSpawnTransform;
	this->BallisticVelocity = InBallisticVelocity;
	this->DamageRange = InDamageRange;
	this->Damage = InDamage;
	this->TrackingMode = InTrackingMode;
	this->TargetActor = InTargetActor;
}
