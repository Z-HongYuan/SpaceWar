// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_DetectFogOfWarComp.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceWar/Subsystem/SW_FogOfWarSubsystem.h"


class USW_FogOfWarSubsystem;

USW_DetectFogOfWarComp::USW_DetectFogOfWarComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USW_DetectFogOfWarComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USW_DetectFogOfWarComp::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(UpdateVisibilityTimerHandle, this, &ThisClass::UpdateVisibility, CheckTime, true);
}

void USW_DetectFogOfWarComp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(UpdateVisibilityTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void USW_DetectFogOfWarComp::UpdateVisibility()
{
	/*使用额外的识别*/
	FVector2D ScreenPoint;
	//场景到屏幕
	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0); // 单机游戏玩家索引0
	if (PC and UGameplayStatics::ProjectWorldToScreen(PC, GetOwner()->GetActorLocation(), ScreenPoint)) //Actor在屏幕上的XY位置
	{
		if (USW_FogOfWarSubsystem* Subsystem = GetWorld()->GetSubsystem<USW_FogOfWarSubsystem>())
		{
			double Index = (ScreenPoint.Y) * (ScreenPoint.X) + (ScreenPoint.X);
			if (Subsystem->GetFogOfWarData().IsValidIndex(Index))
			{
				GetOwner()->SetActorHiddenInGame(Subsystem->GetFogOfWarData()[Index] <= BooleanValue);
			}
		}
	}
	else
	{
		GetOwner()->SetActorHiddenInGame(false);
	}
	
	/**/
}
