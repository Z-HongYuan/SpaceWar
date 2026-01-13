// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SW_DetectFogOfWarComp.generated.h"

/*
 * 专门用于检测战争迷雾的组件,此组件为子组件,需要搭配
 * 如果处于战争迷雾中,则隐藏自身
 * 主要作用是,用固定的RenderTarget进行检测,通过阈值判定是否隐藏
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USW_DetectFogOfWarComp : public UActorComponent
{
	GENERATED_BODY()

public:
	USW_DetectFogOfWarComp();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/*
	 * 专门用于更新可视性,在战争迷雾下
	 */
	void UpdateVisibility();

public:
	//检测的间隔
	UPROPERTY(Category="SpaceWar|Fog of War", EditDefaultsOnly)
	float CheckTime = 0.2f;

	//检测R通道的阈值
	UPROPERTY(Category="SpaceWar|Fog of War", EditDefaultsOnly, meta=(ClampMin = "0.0", ClampMax = "255"))
	float BooleanValue = 0.f;

	FTimerHandle UpdateVisibilityTimerHandle;
};
