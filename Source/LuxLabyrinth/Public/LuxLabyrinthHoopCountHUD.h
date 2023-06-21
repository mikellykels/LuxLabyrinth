// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LuxLabyrinthHoopCountHUD.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class LUXLABYRINTH_API ULuxLabyrinthHoopCountHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* HoopCountTextBlock;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHoopCount(int32 TotalHoops, int32 ActivatedHoops);
};
