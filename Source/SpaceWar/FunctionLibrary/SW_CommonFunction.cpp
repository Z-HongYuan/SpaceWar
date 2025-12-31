// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CommonFunction.h"


USaveGame* USW_CommonFunction::BFL_GetSaveGameObject(const FString& SlotName, const int32 UserIndex, TSubclassOf<USaveGame> SaveGameClass)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		return UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);
	}
	else
	{
		return UGameplayStatics::CreateSaveGameObject(SaveGameClass);
	}
}
