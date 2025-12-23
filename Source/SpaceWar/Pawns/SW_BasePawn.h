// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceWar/Components/SW_GridBuildComponent.h"
#include "SW_BasePawn.generated.h"

class UGameplayCameraComponent;
/*
 * 基础Pawn
 * 创建局内局外公有的函数
 */
UCLASS(Abstract)
class SPACEWAR_API ASW_BasePawn : public APawn
{
	GENERATED_BODY()

public:
	ASW_BasePawn();

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	/*
	 * 基础Mesh
	 */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	/*
	 * 摄像机
	 */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGameplayCameraComponent> GameplayCamera;

	/*
	 * 网格组件
	 */
	UPROPERTY(Category=Pawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USW_GridBuildComponent> GridBuildComponent;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SpaceWar")
	FORCEINLINE UGameplayCameraComponent* GetGameplayCamera() const { return GameplayCamera; }
};
