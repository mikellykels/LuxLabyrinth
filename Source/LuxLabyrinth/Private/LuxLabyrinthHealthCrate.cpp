// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthHealthCrate.h"
#include "LuxLabyrinth/LuxLabyrinthCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ALuxLabyrinthHealthCrate::ALuxLabyrinthHealthCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALuxLabyrinthHealthCrate::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ALuxLabyrinthCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	// Bind the OnOverlapBegin function to the sphere's OnComponentBeginOverlap event
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALuxLabyrinthHealthCrate::OnOverlapBegin);
}

// Called every frame
void ALuxLabyrinthHealthCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);

	// Make the widget face the player.
	if (PlayerCharacter && WidgetComponent)
	{
		FRotator LookAtRotation = (PlayerCharacter->GetActorLocation() - GetActorLocation()).Rotation();
		WidgetComponent->SetWorldRotation(LookAtRotation);
	}
}

void ALuxLabyrinthHealthCrate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(ALuxLabyrinthCharacter::StaticClass()))
	{
		ALuxLabyrinthCharacter* LuxCharacter = Cast<ALuxLabyrinthCharacter>(OtherActor);
		if (LuxCharacter)
		{
			LuxCharacter->AddHealth(HealthAmount);

			//SoundCue Triggers
			if (CollectSound)
			{
				FVector HealthCrateLocation = GetActorLocation();
				UGameplayStatics::PlaySoundAtLocation(this, CollectSound, HealthCrateLocation);
			}

			this->Destroy();
		}
	}
}

