// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_GridBuildComponent.h"

#include "SW_FloatingPawnMovement.h"
#include "SpaceWar/Data/SW_CollisionChannels.h"


USW_GridBuildComponent::USW_GridBuildComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USW_GridBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentBuildingState == EBuildingCompState::EBCS_Building)
	{
		UpdateCursorBuildingLocation();
	}
}

void USW_GridBuildComponent::RotateHeldBuilding()
{
	if (!HeldBuilding) return;

	HeldBuilding->SetCurrentRotate((HeldBuilding->GetCurrentRotate() + 90) % 360);
	HeldBuilding->SetActorRotation(HeldBuilding->GetActorRotation().Add(0, 90, 0));

	//CheckAndHighlight
	CheckAndHighlight(HeldBuilding->GetActorLocation(), HeldBuilding->GetShapeFootPrint());
}

void USW_GridBuildComponent::CleanHighlight()
{
	for (ASW_Cell*& Element : PreHighlightArray)
	{
		//改变外观
		Element->SetCellState(ECellState::ECS_Idle);
	}
}

bool USW_GridBuildComponent::CheckAndHighlight(const FVector& InVector, const TArray<FIntPoint>& InFootPrint)
{
	if (CurrentBuildingState != EBuildingCompState::EBCS_Building) return false;

	CleanHighlight();

	bool bCanBuild = true;

	TArray<ASW_Cell*> WaitToHighlight = {};

	ECellState FinalCellState;

	/*
	 * 通过射线检测Cells来访问是否可用,并且添加其他限制
	 */
	for (const FIntPoint& Point : InFootPrint)
	{
		FVector TraceStartLocation = InVector + FVector(Point.X * CELL_SIZE, Point.Y * CELL_SIZE, 0);
		FVector TraceEndLocation = TraceStartLocation - FVector(0, 0, 1000);
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, TraceStartLocation, TraceEndLocation, ECC_Object_Cell);

		/*检查是否有Cells*/
		if (!bHit or !HitResult.GetActor())
		{
			bCanBuild = false;
			break;
		}

		/*检查Cells上的占位标记*/
		ASW_Cell* Cell = Cast<ASW_Cell>(HitResult.GetActor());
		if (HitResult.GetActor() and Cell)
		{
			if (Cell) WaitToHighlight.AddUnique(Cell);
			if (Cell->GetIsOccupied())
			{
				bCanBuild = false;
				break;
			}
		}

		//命中位置跟中心位置误差不小于阈值
		if (FVector::DistXY(HitResult.GetActor()->GetActorLocation(), HitResult.Location) >= CheckRange)
		{
			bCanBuild = false;
			break;
		}

		/*检查是否拥有建筑的Tag*/
		if (!Cell->GetAllowTags().HasTagExact(HeldBuilding->GetBuildingTag()))
		{
			bCanBuild = false;
			break;
		}
	}

	bCanBuild ? FinalCellState = ECellState::ECS_CanBuild : FinalCellState = ECellState::ECS_CannotBuild;

	for (ASW_Cell*& Element : WaitToHighlight)
	{
		Element->SetCellState(FinalCellState);
		PreHighlightArray.AddUnique(Element);
	}

	return bCanBuild;
}

void USW_GridBuildComponent::CommitBuildingToGrid()
{
	if (!HeldBuilding) return;


	for (FIntPoint& Point : HeldBuilding->GetShapeFootPrint())
	{
		FVector TraceStartLocation = HeldBuilding->GetActorLocation() + FVector(Point.X * CELL_SIZE, Point.Y * CELL_SIZE, 0);
		FVector TraceEndLocation = TraceStartLocation - FVector(0, 0, 1000);
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, TraceStartLocation, TraceEndLocation, ECC_Object_Cell);
		if (bHit and HitResult.GetActor())
		{
			if (ASW_Cell* Cell = Cast<ASW_Cell>(HitResult.GetActor()))
			{
				Cell->SetIsOccupied(true);
				//这个仅用于建造模式下的销毁
				Cell->OccupiedActor = HeldBuilding;
			}
		}
	}

	//绑定建筑到Actor上
	HeldBuilding->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);

	CleanHighlight();
	HeldBuilding->OnBuilded();
	HeldBuilding = nullptr;
	CurrentBuildingState = EBuildingCompState::EBCS_Idle;
}

void USW_GridBuildComponent::CancelCurrentAction()
{
	if (CurrentBuildingState == EBuildingCompState::EBCS_Building)
	{
		if (!HeldBuilding) return;
		HeldBuilding->Destroy();
		HeldBuilding = nullptr;
		CleanHighlight();
		CurrentBuildingState = EBuildingCompState::EBCS_Idle;
	}
	else if (CurrentBuildingState == EBuildingCompState::EBCS_Selecting)
	{
		if (!SelectedBuilding) return;
		SelectedBuilding->SetIsSelected(false);
		SelectedBuilding = nullptr;
		CurrentBuildingState = EBuildingCompState::EBCS_Idle;
	}
}

void USW_GridBuildComponent::SelectBuildingOnGrid(ASW_BuildingActor* InBuilding)
{
	if (!InBuilding) return;

	CancelCurrentAction();
	SelectedBuilding = InBuilding;
	SelectedBuilding->SetIsSelected(true);

	CurrentBuildingState = EBuildingCompState::EBCS_Selecting;
}

void USW_GridBuildComponent::UnSelectBuild()
{
	if (!SelectedBuilding) return;
	SelectedBuilding->SetIsSelected(false);
	SelectedBuilding = nullptr;
	CurrentBuildingState = EBuildingCompState::EBCS_Idle;
}

void USW_GridBuildComponent::DeleteSelectBuilding()
{
	if (!SelectedBuilding) return;
	//消除占位信息
	for (FIntPoint& Point : SelectedBuilding->GetShapeFootPrint())
	{
		FVector TraceStartLocation = SelectedBuilding->GetActorLocation() + FVector(Point.X * CELL_SIZE, Point.Y * CELL_SIZE, 0);
		FVector TraceEndLocation = TraceStartLocation - FVector(0, 0, 1000);
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, TraceStartLocation, TraceEndLocation, ECC_Object_Cell);
		if (bHit and HitResult.GetActor())
		{
			if (ASW_Cell* Cell = Cast<ASW_Cell>(HitResult.GetActor()))
			{
				Cell->SetIsOccupied(false);
				Cell->OccupiedActor = nullptr;
			}
		}
	}

	//解绑建筑
	SelectedBuilding->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	//删除建筑物
	SelectedBuilding->Destroy();
	SelectedBuilding = nullptr;
	CurrentBuildingState = EBuildingCompState::EBCS_Idle;
}

void USW_GridBuildComponent::UpdateCursorBuildingLocation()
{
	if (!HeldBuilding) return;
	if (CurrentBuildingState != EBuildingCompState::EBCS_Building) return;

	//移动到Cell的中心位置上
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		FHitResult HitResult;
		if (PC->GetHitResultUnderCursor(ECC_Object_Cell, false, HitResult))
		{
			if (HitResult.GetActor())
			{
				HeldBuilding->SetActorLocation(HitResult.GetActor()->GetActorLocation());
			}
		}
	}

	CheckAndHighlight(HeldBuilding->GetActorLocation(), HeldBuilding->GetShapeFootPrint());
}

void USW_GridBuildComponent::SpawnAndAttachBuilding(TSubclassOf<ASW_BuildingActor> InBuildingClass)
{
	CancelCurrentAction();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner<APawn>();

	HeldBuilding = GetWorld()->SpawnActor<ASW_BuildingActor>(InBuildingClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	CurrentBuildingState = EBuildingCompState::EBCS_Building;
	UpdateCursorBuildingLocation();
}

void USW_GridBuildComponent::Rotate_Handle()
{
	if (CurrentBuildingState != EBuildingCompState::EBCS_Building) return;
	RotateHeldBuilding();
}

void USW_GridBuildComponent::Delete_Handle()
{
	if (CurrentBuildingState != EBuildingCompState::EBCS_Selecting) return;
	DeleteSelectBuilding();
}

void USW_GridBuildComponent::Confirm_Handle()
{
	FHitResult HitResult;
	switch (CurrentBuildingState)
	{
	case EBuildingCompState::EBCS_Idle:

		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
			if (PC->GetHitResultUnderCursor(ECC_Object_Building, false, HitResult))
				if (ASW_BuildingActor* HitBuilding = Cast<ASW_BuildingActor>(HitResult.GetActor()))
					SelectBuildingOnGrid(HitBuilding);
		break;

	case EBuildingCompState::EBCS_Building:
		if (!HeldBuilding) break;
		if (CheckAndHighlight(HeldBuilding->GetActorLocation(), HeldBuilding->GetShapeFootPrint()))
			CommitBuildingToGrid();
		break;
	default: ;
	}
}

void USW_GridBuildComponent::Cancel_Handle()
{
	CancelCurrentAction();
}
