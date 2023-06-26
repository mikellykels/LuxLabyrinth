// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthStreetLightPost.h"
#include "Components/PointLightComponent.h"

// Sets default values
ALuxLabyrinthStreetLightPost::ALuxLabyrinthStreetLightPost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLight->SetupAttachment(Root);
	PointLight->SetVisibility(false);

	bIsLit = false;

}

// Called when the game starts or when spawned
void ALuxLabyrinthStreetLightPost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALuxLabyrinthStreetLightPost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTimerHandle ALuxLabyrinthStreetLightPost::LightUp()
{
	FTimerHandle TimerHandle;
	if (!bIsLit)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				PointLight->SetVisibility(true);
				bIsLit = true;
			}, 0.5f, false);
	}
	return TimerHandle;
}

