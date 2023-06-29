// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthHoop.h"
#include "LuxLabyrinthBuilding.h"
#include "LuxLabyrinthHoopCountHUD.h"
#include "LuxLabyrinthStreetLightPost.h"
#include "LuxLabyrinth/LuxLabyrinthCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALuxLabyrinthHoop::ALuxLabyrinthHoop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoopMesh"));
	RootComponent = HoopMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(HoopMesh);

	CurrentBuildingIndex = 0;
	CurrentLightPostIndex = 0;
}

// Called when the game starts or when spawned
void ALuxLabyrinthHoop::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALuxLabyrinthHoop::OnPassedThrough);
}

// Called every frame
void ALuxLabyrinthHoop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALuxLabyrinthHoop::OnPassedThrough(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bHasBeenActivated && OtherActor->IsA(ALuxLabyrinthCharacter::StaticClass()))
	{
		bHasBeenActivated = true;
		LightUpNextBuilding();
		LightUpNextLight();
		OnHoopActivated.Broadcast();
	}
}

void ALuxLabyrinthHoop::LightUpNextBuilding()
{
	if (CurrentBuildingIndex < Buildings.Num())
	{
		ALuxLabyrinthBuilding* Building = Buildings[CurrentBuildingIndex];
		if (Building)
		{
			Building->LightUp();
		}

		CurrentBuildingIndex++;

		// Schedule to light up the next building after a delay
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALuxLabyrinthHoop::LightUpNextBuilding, 0.5f, false);
	}
}

void ALuxLabyrinthHoop::LightUpNextLight()
{
	if (CurrentLightPostIndex < LightPosts.Num())
	{
		ALuxLabyrinthStreetLightPost* LightPost = LightPosts[CurrentLightPostIndex];
		if (LightPost)
		{
			LightPost->LightUp();
		}

		CurrentLightPostIndex++;

		// Schedule to light up the next light after a delay
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALuxLabyrinthHoop::LightUpNextLight, 0.10f, false);
	}
}

