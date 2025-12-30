// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_GridBuildComponent.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceWar/SaveGame/SW_SaveGame.h"


USW_GridBuildComponent::USW_GridBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USW_GridBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentBuildingState == EBuildingState::EBS_Building)
	{
		UpdateCursorBuildingLocation();
	}
}

void USW_GridBuildComponent::BeginPlay()
{
	Super::BeginPlay();

	InitGrid();
}

FVector USW_GridBuildComponent::GetGridOrigin()
{
	FVector Origin = GetOwner()->GetActorLocation();
	Origin -= FVector(CellSize * Width / 2, CellSize * Height / 2, 0);
	return Origin;
}

FIntPoint USW_GridBuildComponent::GetPointFromWorldLocation(const FVector& InLocation)
{
	FVector TempLocation = InLocation - GetGridOrigin();
	TempLocation.X /= CellSize;
	TempLocation.Y /= CellSize;
	return FIntPoint(floor(TempLocation.X), floor(TempLocation.Y));
}

FVector USW_GridBuildComponent::GetWorldLocationFromPoint(const FIntPoint& InPoint)
{
	return GetGridOrigin() + FVector(InPoint.X * CellSize + CellSize / 2, InPoint.Y * CellSize + CellSize / 2, 0.f);
}

bool USW_GridBuildComponent::IsValidPoint(const FIntPoint& InPoint)
{
	/*
	 * 意味着索引有效,必须在0~长宽的范围内
	 */
	return InPoint.X >= 0
		and InPoint.X < Width
		and InPoint.Y >= 0
		and InPoint.Y < Height;
}

ASW_Cell* USW_GridBuildComponent::GetCellFromPoint(const FIntPoint& InPoint)
{
	if (!IsValidPoint(InPoint)) return nullptr;
	int32 Index = InPoint.X + InPoint.Y * Width;
	if (Index > GridArray.Num() and Index < 0) return nullptr;

	return GridArray[Index];
}

ASW_Cell* USW_GridBuildComponent::GetCellFromWorldLocation(const FVector& InLocation)
{
	return GetCellFromPoint(GetPointFromWorldLocation(InLocation));
}

void USW_GridBuildComponent::RotateHeldBuilding()
{
	if (!HeldBuilding) return;

	HeldBuilding->SetCurrentRotate((HeldBuilding->GetCurrentRotate() + 90) % 360);
	HeldBuilding->SetActorRotation(HeldBuilding->GetActorRotation().Add(0, 90, 0));

	//CheckAndHighlight
	CheckAndHighlight(GetCellFromWorldLocation(HeldBuilding->GetActorLocation())->GetCellPosition(), HeldBuilding->GetShapeFootPrint());
}

void USW_GridBuildComponent::CleanHighlight()
{
	for (ASW_Cell* Element : PreHighlightArray)
	{
		//改变外观
		Element->SetCellState(ECellState::ECS_Idle);
	}
}

bool USW_GridBuildComponent::CheckAndHighlight(const FIntPoint& InPoint, const TArray<FIntPoint>& InFootPrint)
{
	if (CurrentBuildingState != EBuildingState::EBS_Building) return false;

	CleanHighlight();

	bool bCanBuild = true;

	TArray<ASW_Cell*> WaitToHighlight = {};

	ECellState FinalCellState = ECellState::ECS_Idle;

	for (FIntPoint Element : InFootPrint)
	{
		FIntPoint Temp;
		Temp = Element + InPoint;
		if (!IsValidPoint(Temp))
		{
			bCanBuild = false;
			break;
		}
		if (GetCellFromPoint(Temp))
		{
			WaitToHighlight.Add(GetCellFromPoint(Temp));

			if (GetCellFromPoint(Temp)->GetIsOccupied()) bCanBuild = false;
		}
	}
	bCanBuild ? FinalCellState = ECellState::ECS_CanBuild : FinalCellState = ECellState::ECS_CannotBuild;

	for (ASW_Cell* Element : WaitToHighlight)
	{
		Element->SetCellState(FinalCellState);
		PreHighlightArray.Add(Element);
	}

	return bCanBuild;
}

void USW_GridBuildComponent::CommitBuildingToGrid()
{
	if (!HeldBuilding) return;

	//建筑物的原点
	ASW_Cell* OriginCell = GetCellFromWorldLocation(HeldBuilding->GetActorLocation());

	for (FIntPoint Element : HeldBuilding->GetShapeFootPrint())
	{
		FIntPoint Point;
		Point = OriginCell->GetCellPosition() + Element;
		if (IsValidPoint(Point))
		{
			if (ASW_Cell* Cell = GetCellFromPoint(Point))
			{
				Cell->SetIsOccupied(true);
			}
		}
	}

	//绑定建筑到Actor上
	HeldBuilding->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);

	CleanHighlight();
	HeldBuilding->OnBuilded();
	HeldBuilding = nullptr;
	CurrentBuildingState = EBuildingState::EBS_Idle;
}

void USW_GridBuildComponent::CancelCurrentAction()
{
	if (CurrentBuildingState == EBuildingState::EBS_Building)
	{
		if (!HeldBuilding) return;
		HeldBuilding->Destroy();
		HeldBuilding = nullptr;
		CleanHighlight();
		CurrentBuildingState = EBuildingState::EBS_Idle;
	}
	else if (CurrentBuildingState == EBuildingState::EBS_Selecting)
	{
		if (!SelectedBuilding) return;
		SelectedBuilding->SetIsSelected(false);
		SelectedBuilding = nullptr;
		CurrentBuildingState = EBuildingState::EBS_Idle;
	}
}

void USW_GridBuildComponent::SelectBuildingOnGrid(ASW_BuildingActor* InBuilding)
{
	if (!InBuilding) return;

	CancelCurrentAction();
	SelectedBuilding = InBuilding;
	SelectedBuilding->SetIsSelected(true);

	CurrentBuildingState = EBuildingState::EBS_Selecting;
}

void USW_GridBuildComponent::UnSelectBuild()
{
	if (!SelectedBuilding) return;
	SelectedBuilding->SetIsSelected(false);
	SelectedBuilding = nullptr;
	CurrentBuildingState = EBuildingState::EBS_Idle;
}

void USW_GridBuildComponent::DeleteSelectBuilding()
{
	if (!SelectedBuilding) return;
	//消除占位信息
	ASW_Cell* CellCenter = GetCellFromWorldLocation(SelectedBuilding->GetActorLocation());
	for (FIntPoint Element : SelectedBuilding->GetShapeFootPrint())
	{
		FIntPoint Point;
		Point = CellCenter->GetCellPosition() + Element;
		if (IsValidPoint(Point))
		{
			if (ASW_Cell* Cell = GetCellFromPoint(Point))
			{
				Cell->SetIsOccupied(false);
			}
		}
	}

	//解绑建筑
	SelectedBuilding->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	//删除建筑物
	SelectedBuilding->Destroy();
	SelectedBuilding = nullptr;
	CurrentBuildingState = EBuildingState::EBS_Idle;
}

void USW_GridBuildComponent::UpdateCursorBuildingLocation()
{
	if (!HeldBuilding) return;
	if (CurrentBuildingState != EBuildingState::EBS_Building) return;

	FVector WorldLocation;
	FVector WorldDirection;
	bool bIsSuccess = UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	if (!bIsSuccess) return;

	FHitResult HitResult;
	bIsSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * 100000, ECC_Visibility);
	if (!bIsSuccess) return;

	ASW_Cell* HitCell = GetCellFromWorldLocation(HitResult.Location);
	if (!HitCell) return;

	HeldBuilding->SetActorLocation(GetWorldLocationFromPoint(HitCell->GetCellPosition()));

	CheckAndHighlight(HitCell->GetCellPosition(), HeldBuilding->GetShapeFootPrint());
}

void USW_GridBuildComponent::SpawnAndAttachBuilding(TSubclassOf<ASW_BuildingActor> InBuildingClass)
{
	CancelCurrentAction();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner<APawn>();
	HeldBuilding = GetWorld()->SpawnActor<ASW_BuildingActor>(InBuildingClass, GetGridOrigin(), FRotator::ZeroRotator, SpawnParams);

	CurrentBuildingState = EBuildingState::EBS_Building;
	UpdateCursorBuildingLocation();
}


void USW_GridBuildComponent::InitGrid()
{
	for (int Y = 0; Y < Height; ++Y)
	{
		for (int X = 0; X < Width; ++X)
		{
			if (!CellClass) continue;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetOwner<APawn>();
			ASW_Cell* Spawned = GetWorld()->SpawnActor<ASW_Cell>(CellClass, GetWorldLocationFromPoint(FIntPoint(X, Y)), FRotator::ZeroRotator, SpawnParams);
			Spawned->SetCellPosition(FIntPoint(X, Y));
			GridArray.Add(Spawned);

			//附加到Pawn上
			Spawned->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void USW_GridBuildComponent::Rotate_Handle()
{
	if (CurrentBuildingState != EBuildingState::EBS_Building) return;
	RotateHeldBuilding();
}

void USW_GridBuildComponent::Delete_Handle()
{
	if (CurrentBuildingState != EBuildingState::EBS_Selecting) return;
	DeleteSelectBuilding();
}

void USW_GridBuildComponent::Confirm_Handle()
{
	FHitResult HitResult;
	bool bIsSuccess;
	switch (CurrentBuildingState)
	{
	case EBuildingState::EBS_Idle:
		FVector WorldLocation;
		FVector WorldDirection;
		bIsSuccess = UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		if (!bIsSuccess) break;

		bIsSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * 100000, ECC_Visibility);
		if (!bIsSuccess) break;

		if (ASW_BuildingActor* HitBuilding = Cast<ASW_BuildingActor>(HitResult.GetHitObjectHandle().FetchActor()))
		{
			SelectBuildingOnGrid(HitBuilding);
		}

		break;

	case EBuildingState::EBS_Building:
		if (!HeldBuilding) break;
		if (ASW_Cell* Cell = GetCellFromWorldLocation(HeldBuilding->GetActorLocation()))
		{
			if (CheckAndHighlight(Cell->GetCellPosition(), HeldBuilding->GetShapeFootPrint()))
			{
				CommitBuildingToGrid();
			}
		}

		break;
	}
}

void USW_GridBuildComponent::Cancel_Handle()
{
	CancelCurrentAction();
}

void USW_GridBuildComponent::ReBuildActorFromSaveGame(USW_SaveGame* InSaveGame)
{
	if (!InSaveGame) return;

	for (const FBuildingSaveData& Element : InSaveGame->BuildingSaveData)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetOwner<APawn>();
		ASW_BuildingActor* SpawnedBuilding = GetWorld()->SpawnActor<ASW_BuildingActor>(Element.BuildingClass, GetWorldLocationFromPoint(Element.GridCoord), Element.CurrentRotate,
		                                                                               SpawnParams);
		SpawnedBuilding->OnBuilded();

		//绑定到Actor
		SpawnedBuilding->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	}
}

void USW_GridBuildComponent::SaveActorToSaveGame(USW_SaveGame* InSaveGame)
{
	if (!InSaveGame) return;
	InSaveGame->BuildingSaveData.Empty();

	TArray<AActor*> BuildingArray;
	UGameplayStatics::GetAllActorsOfClass(this, ASW_BuildingActor::StaticClass(), BuildingArray);

	for (AActor* Element : BuildingArray)
	{
		ASW_BuildingActor* Building = Cast<ASW_BuildingActor>(Element);
		if (!Building) continue;

		InSaveGame->BuildingSaveData.Add(
			FBuildingSaveData(
				Building->GetClass(),
				Building->GetBuildingGridType(),
				Building->GetActorRotation(),
				GetPointFromWorldLocation(Building->GetActorLocation())
			));
	}
}
