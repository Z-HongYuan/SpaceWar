// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_AttributeSetBase.h"

#include "GameplayEffectExtension.h"

USW_AttributeSetBase::USW_AttributeSetBase()
{
}

void USW_AttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());

	if (Attribute == GetMaxSpeedAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, 9999);

	if (Attribute == GetFuelAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxFuel());
}

void USW_AttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

	if (Data.EvaluatedData.Attribute == GetMaxSpeedAttribute())
		SetMaxSpeed(FMath::Clamp(GetMaxSpeed(), 0.f, 9999));

	if (Data.EvaluatedData.Attribute == GetFuelAttribute())
		SetFuel(FMath::Clamp(GetFuel(), 0.f, GetMaxFuel()));
}
