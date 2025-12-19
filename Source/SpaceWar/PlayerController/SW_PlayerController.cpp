// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ASW_PlayerController::ASW_PlayerController()
{
}

void ASW_PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASW_PlayerController::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);

	ChangeInputContext(DefaultInputContext, 0, true);
}

void ASW_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	ChangeInputContext(DefaultInputContext, 0, false);
}

void ASW_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::PawnMove);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::PawnMove);
	}
}

void ASW_PlayerController::PawnMove(const FInputActionValue& Value)
{
	if (!GetPawn()) return;
	GetPawn()->AddMovementInput(Value.Get<FVector>());
}

void ASW_PlayerController::PawnLook(const FInputActionValue& Value)
{
	AddYawInput(Value.Get<FVector>().X);
	AddPitchInput(Value.Get<FVector>().Y);
}

void ASW_PlayerController::ChangeInputContext(UInputMappingContext* Context, int32 Priority, bool bIsAdd)
{
	if (!IsLocalController()) return;

	if (const ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			bIsAdd ? Subsystem->AddMappingContext(Context, Priority) : Subsystem->RemoveMappingContext(Context);
		}
	}
}
