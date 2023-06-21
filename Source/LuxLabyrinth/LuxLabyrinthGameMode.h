// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LuxLabyrinthGameMode.generated.h"

class ULuxLabyrinthHoopCountHUD;

UCLASS(minimalapi)
class ALuxLabyrinthGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALuxLabyrinthGameMode();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHoopActivated();

	UFUNCTION(BlueprintCallable, Category = "Hoop")
	ULuxLabyrinthHoopCountHUD* GetHoopHud() const;

private:
	int32 TotalHoops;
	int32 ActivatedHoops;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HoopCountHUDClass;

	UPROPERTY()
	ULuxLabyrinthHoopCountHUD* HoopCountHUD;
};



