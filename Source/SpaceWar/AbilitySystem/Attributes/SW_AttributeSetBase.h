// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "SW_AttributeSetBase.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/*How To Use	ATTRIBUTE_ACCESSORS(UMyHealthSet, Health)*/

/**
 * 
 */
UCLASS()
class SPACEWAR_API USW_AttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	USW_AttributeSetBase();

	/*
	 * 限制函数
	 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/*
	 * 生命值,限制到 0~MaxHealth
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, Health)

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, MaxHealth)

	/*
	 * 最大速度,限制到 0~9999
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, MaxSpeed)

	/*
	 * 基础燃料,限制到 0~MaxFuel
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData Fuel;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, Fuel)

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData MaxFuel;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, MaxFuel)

	/*
	 * 视野范围,未限制,需要映射
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData ViewRange;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, ViewRange)

	/*
	 * 加速度,限制到 0~9999
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData Acceleration;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, Acceleration)

	/*
	 * 燃料消耗,未限制
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData FuelCost;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, FuelCost)

	/*
	 * 电力值,限制到 0~最大电力值
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, Power)

	/*
	 * 最大电力值
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpaceWar")
	FGameplayAttributeData MaxPower;
	ATTRIBUTE_ACCESSORS(USW_AttributeSetBase, MaxPower)
};
