// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_GridBuildComponent.h"


USW_GridBuildComponent::USW_GridBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USW_GridBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDebug) Debug();
}

void USW_GridBuildComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USW_GridBuildComponent::UpdateGridCells()
{
	GridCells.Add(FIntPoint(0, 0), FGridCell());
	GridCells.Add(FIntPoint(0, 1), FGridCell());
	GridCells.Add(FIntPoint(1, 1), FGridCell());
	GridCells.Add(FIntPoint(1, 0), FGridCell());


	/*
	 * 添加网格体组件
	 */
	for (auto& [Position, Cell] : GridCells)
	{
		/*
		 * 设置参数
		 */
		Cell.Position = Position;
		Cell.State = EGridState::EGS_Unlocked;
		Cell.GridMesh = GridMesh;


		if (Cell.State == EGridState::EGS_Locked)
		{
			//设置材质颜色
			// continue;
		}

		FVector Location = FVector(Position.X * GridSize, Position.Y * GridSize, 0.f);

		UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(this);
		Mesh->SetStaticMesh(GridMesh.LoadSynchronous());
		Mesh->SetupAttachment(GetOwner()->GetRootComponent());
		Mesh->SetRelativeLocation(Location);
		Mesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	}
}

void USW_GridBuildComponent::Debug()
{
	//Debug
	for (auto& [Position, Cell] : GridCells)
	{
		FVector Location = FVector(Position.X * GridSize, Position.Y * GridSize, 0.f);
		DrawDebugSphere(GetWorld(), Location, 20.0f, 12, FColor::Red, false, 0);
	}
}
