// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/EngineTypes.h"

/*
 * !!!关联于 Engine.ini !!!
 * #include "../Config/DefaultEngine.ini"
 */

/*
 * 对象通道枚举 / Object Channel Enum
 * 用于证明自身是什么对象
 */
// +DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Overlap,bTraceType=False,bStaticObject=False,Name="Projectile")
// +DefaultChannelResponses=(Channel=ECC_GameTraceChannel2,DefaultResponse=ECR_Ignore,bTraceType=False,bStaticObject=False,Name="Building")
// +DefaultChannelResponses=(Channel=ECC_GameTraceChannel3,DefaultResponse=ECR_Ignore,bTraceType=False,bStaticObject=False,Name="Cell")

//自身是Projectile
#define ECC_Object_Projectile ECC_GameTraceChannel1

//自身是Building
#define ECC_Object_Building ECC_GameTraceChannel2

//自身是Cell
#define ECC_Object_Cell ECC_GameTraceChannel3


/*
 * 检测通道枚举 / Trace Channel Enum
 * 用于在Trace中使用的检测对象
 */

// +DefaultChannelResponses=(Channel=ECC_GameTraceChannel4,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=False,Name="Enemy")

//检查敌人通道
#define ECC_Trace_Enemy ECC_GameTraceChannel4
