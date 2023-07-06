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

	UFUNCTION(BlueprintCallable, Category = "Hoop")
	void OnHoopActivated();

	UFUNCTION(BlueprintCallable, Category = "Hoop")
	ULuxLabyrinthHoopCountHUD* GetHoopHud() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hoop")
	int32 TotalHoops;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hoop")
	int32 ActivatedHoops;

private:
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> HoopCountHUDClass;

	UPROPERTY()
	ULuxLabyrinthHoopCountHUD* HoopCountHUD;
};



