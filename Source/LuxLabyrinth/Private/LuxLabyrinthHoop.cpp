// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthHoop.h"
#include "LuxLabyrinthHoopCountHUD.h"
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
		OnHoopActivated.Broadcast();
	}
}

