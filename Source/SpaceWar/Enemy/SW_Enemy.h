// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponent.h"
#include "GameFramework/Actor.h"
#include "SW_Enemy.generated.h"

/*
 * 简单Enemy
 * 有初始血量
 * 只会执行状态树,并且受到伤害
 */
UCLASS()
class SPACEWAR_API ASW_Enemy : public AActor
{
	GENERATED_BODY()

public:
	ASW_Enemy();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStateTreeComponent> StateTreeComponent;

public:
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn), Category = "Enemy")
	float Health;
};
