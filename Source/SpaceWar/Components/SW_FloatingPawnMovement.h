// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SW_FloatingPawnMovement.generated.h"

/*
 * 自定义的漂浮组件
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USW_FloatingPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:
	USW_FloatingPawnMovement();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 * 当输入调用的时候,检查规则
	 */
	virtual void AddInputVector(FVector WorldVector, bool bForce = false) override;

	/*
	 * 关联AttributeSet内的属性
	 */
	virtual float GetMaxSpeed() const override;

protected:
	virtual void BeginPlay() override;

private:

	
public:
	//	FORCEINLINE void SetMaxSpeed(const float& InMaxSpeed) { MaxSpeed = InMaxSpeed; }
};
