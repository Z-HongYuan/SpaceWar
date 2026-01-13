// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CommonFunction.h"

#include "Engine/TextureRenderTarget2D.h"


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

bool USW_CommonFunction::BFL_GetRenderTargetPointValue(UTextureRenderTarget2D* RenderTarget, TArray<uint8>& OutValue)
{
	// OutValue = {};不要置空
	if (!RenderTarget) return false;
	FTextureRenderTarget2DResource* RTResource = static_cast<FTextureRenderTarget2DResource*>(RenderTarget->GameThread_GetRenderTargetResource());
	if (!RTResource) return false;

	const int32 SizeX = RenderTarget->SizeX;
	const int32 SizeY = RenderTarget->SizeY;

	const EPixelFormat Format = RenderTarget->GetFormat();

	/* ================= PF_G8 / RTF_R8 ================= */
	if (Format == PF_G8)
	{
		TArray<FColor> Pixels;
		RTResource->ReadPixels(Pixels);
		OutValue.SetNum(Pixels.Num());
		for (int i = 0; i < Pixels.Num(); ++i)
		{
			OutValue[i] = Pixels[i].R;
		}

		// const int32 Index = Point.Y * SizeX + Point.X;
		// OutValue = Pixels.IsValidIndex(Index) ? Pixels[Index].R : 0.f;
		return true;
	}

	return false;
}
