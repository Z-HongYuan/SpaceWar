// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_SaveGame.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceWar/Building/SW_BuildingActor.h"
#include "SpaceWar/Building/SW_Cell.h"
#include "SpaceWar/Components/SW_FloatingPawnMovement.h"
#include "SpaceWar/Data/SW_CollisionChannels.h"

void USW_SaveGame::ReBuildActorFromSaveGame(UObject* WorldContextObject)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(WorldContextObject, 0);
	if (!PlayerPawn) return;

	TArray<ASW_BuildingActor*> TempBuildingArray = {};

	for (const FBuildingSaveData& Element : BuildingSaveData)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = PlayerPawn;
		SpawnParams.Instigator = PlayerPawn;
		ASW_BuildingActor* SpawnedBuilding = WorldContextObject->GetWorld()->SpawnActor<ASW_BuildingActor>(Element.BuildingClass, SpawnParams);
		SpawnedBuilding->SetActorLocation(Element.BuildingTransform.GetLocation());
		SpawnedBuilding->SetActorRotation(Element.BuildingTransform.GetRotation());

		SpawnedBuilding->OnBuilded();
		SpawnedBuilding->AttachToActor(PlayerPawn, FAttachmentTransformRules::KeepRelativeTransform);

		TempBuildingArray.Add(SpawnedBuilding);
	}

	/*
	 * 建造组件准备好了之后,才能再调用移动组件中
	 */
	PlayerPawn->ForEachComponent<USW_FloatingPawnMovement>(
		false,
		[](USW_FloatingPawnMovement* Component)
		{
			Component->UpdatePropellerArray();
		});

	/*
	 * 重建父子关系
	 */
	for (ASW_BuildingActor*& Element : TempBuildingArray)
	{
		TArray<FIntPoint> PointSet = Element->GetShapeFootPrint();
		for (const FIntPoint& Point : PointSet)
		{
			FVector TraceStartLocation = Element->GetActorLocation() + FVector(Point.X * CELL_SIZE, Point.Y * CELL_SIZE, 0.5f);
			FVector TraceEndLocation = TraceStartLocation - FVector(0, 0, 1);
			FHitResult HitResult;
			bool bHit = WorldContextObject->GetWorld()->LineTraceSingleByObjectType(HitResult, TraceStartLocation, TraceEndLocation, ECC_Object_Cell);
			if (bHit and HitResult.GetActor())
			{
				if (ASW_Cell* Cell = Cast<ASW_Cell>(HitResult.GetActor()))
				{
					Cell->SetIsOccupied(true);
					Cell->OccupiedActor = Element;
				}
			}
		}
	}
}

void USW_SaveGame::SaveBuildingToSaveGame(UObject* WorldContextObject)
{
	BuildingSaveData.Empty();

	TArray<AActor*> BuildingArray;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, ASW_BuildingActor::StaticClass(), BuildingArray);

	for (AActor*& Element : BuildingArray)
	{
		const ASW_BuildingActor* Building = Cast<ASW_BuildingActor>(Element);
		if (!Building) continue;

		BuildingSaveData.Add(
			FBuildingSaveData(
				Building->GetClass(),
				Building->GetActorTransform()));
	}
}
