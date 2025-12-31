// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SW_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class SPACEWAR_API ASW_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASW_PlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* APawn) override;

	virtual void OnUnPossess() override;

	virtual void SetupInputComponent() override;

	void PawnMove(const FInputActionValue& Value);
	void PawnLook(const FInputActionValue& Value);
	void PawnRotation(const FInputActionValue& Value);
	void PawnStopMove(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultInputContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RotationAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> StopMoveAction;

public:
	/*
	 * 添加输入上下文(已经默认调用
	 */
	UFUNCTION(blueprintCallable)
	void ChangeInputContext(UInputMappingContext* Context, int32 Priority, bool bIsAdd = true);
};
