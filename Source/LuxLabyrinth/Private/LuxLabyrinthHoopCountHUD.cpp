// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthHoopCountHUD.h"
#include "Components/TextBlock.h"

void ULuxLabyrinthHoopCountHUD::UpdateHoopCount(int32 TotalHoops, int32 ActivatedHoops)
{
	if (HoopCountTextBlock)
	{
		int32 RemainingHoops = TotalHoops - ActivatedHoops;
		HoopCountTextBlock->SetText(FText::Format(NSLOCTEXT("HoopCountHUD", "HoopCountFormat", "Remaining: {0}"), RemainingHoops));
	}
}

void ULuxLabyrinthHoopCountHUD::UpdateMainQuestText(const FString& NewText)
{
	if (MainQuestTextBlock)
	{
		MainQuestTextBlock->SetText(FText::FromString(NewText));
	}
}
