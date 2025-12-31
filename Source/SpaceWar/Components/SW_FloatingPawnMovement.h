// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SpaceWar/Building/BuildingActor/SW_Building_Propeller.h"
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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/*
	 * 当输入调用的时候,检查规则
	 */
	virtual void AddInputVector(FVector WorldVector, bool bForce = false) override;

protected:
	virtual void BeginPlay() override;

private:
	/*
	 * 关联AttributeSet内的属性
	 */
	UFUNCTION()
	void UpdateAttributeDelegate(bool bIsAdd);

	/*
	 * 推进器数组
	 */
	UPROPERTY()
	TArray<ASW_Building_Propeller*> PropellerArray = {};

public:
	//	FORCEINLINE void SetMaxSpeed(const float& InMaxSpeed) { MaxSpeed = InMaxSpeed; }

	/*
	 * 更新推进器
	 */
	void UpdatePropellerArray();

	/*
	 * 旋转事件
	 * 输入为 -1~1,判断为顺时针还是逆时针
	 */
	void AddInputRotation(float InRotation);
	
	/*
	 * 急停事件
	 */
	void EmergencyStop(bool InRotation);
};
