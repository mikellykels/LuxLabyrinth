// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuxLabyrinthGameMode.h"
#include "LuxLabyrinthCharacter.h"
#include "LuxLabyrinthHoop.h"
#include "LuxLabyrinthHoopCountHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ALuxLabyrinthGameMode::ALuxLabyrinthGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/LuxLabyrinth/Blueprints/Characters/BP_Lux"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void ALuxLabyrinthGameMode::BeginPlay()
{
	Super::BeginPlay();

	// find all hoops in the world and count them
	for (TActorIterator<ALuxLabyrinthHoop> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TotalHoops++;
		ActorItr->OnHoopActivated.AddDynamic(this, &ALuxLabyrinthGameMode::OnHoopActivated);
	}

	// Create the HUD widget and add it to the viewport
	if (HoopCountHUDClass)
	{
		HoopCountHUD = CreateWidget<ULuxLabyrinthHoopCountHUD>(GetWorld(), HoopCountHUDClass);
		if (HoopCountHUD)
		{
			HoopCountHUD->SetVisibility(ESlateVisibility::Hidden);
			HoopCountHUD->AddToViewport();
			HoopCountHUD->UpdateHoopCount(TotalHoops, ActivatedHoops);
		}
	}
}

void ALuxLabyrinthGameMode::OnHoopActivated()
{
	ActivatedHoops++;
	if (HoopCountHUD)
	{
		HoopCountHUD->UpdateHoopCount(TotalHoops, ActivatedHoops);
	}
}

ULuxLabyrinthHoopCountHUD* ALuxLabyrinthGameMode::GetHoopHud() const
{
	return HoopCountHUD;
}
