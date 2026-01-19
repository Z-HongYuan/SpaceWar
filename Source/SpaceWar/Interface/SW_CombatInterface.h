// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SW_CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USW_CombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPACEWAR_API ISW_CombatInterface
{
	GENERATED_BODY()

public:
	/*
	 * 用于战斗中,被状态树锁定时调用
	 */
	virtual void OnLocked() = 0;
};
