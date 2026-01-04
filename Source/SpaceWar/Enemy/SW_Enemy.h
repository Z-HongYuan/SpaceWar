// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponent.h"
#include "GameFramework/Actor.h"
#include "SW_Enemy.generated.h"

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
};
