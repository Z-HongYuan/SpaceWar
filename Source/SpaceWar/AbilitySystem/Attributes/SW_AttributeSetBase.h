// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:

private:

public:
};
