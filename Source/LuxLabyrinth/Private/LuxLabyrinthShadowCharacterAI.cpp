// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthShadowCharacterAI.h"
#include "LuxLabyrinth/LuxLabyrinthCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
ALuxLabyrinthShadowCharacterAI::ALuxLabyrinthShadowCharacterAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALuxLabyrinthShadowCharacterAI::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALuxLabyrinthShadowCharacterAI::OnOverlapBegin);
	
}

// Called every frame
void ALuxLabyrinthShadowCharacterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALuxLabyrinthShadowCharacterAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALuxLabyrinthShadowCharacterAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALuxLabyrinthCharacter* LuxCharacter = Cast<ALuxLabyrinthCharacter>(OtherActor);

	if (LuxCharacter != nullptr)
	{
		FDamageEvent DamageEvent;
		LuxCharacter->TakeDamage(LuxCharacter->DamagePerHit, DamageEvent, GetController(), this);
	}

	if (LuxCharacter && LuxCharacter->GetCurrentState() != EState::Dark)
	{
		LuxCharacter->SetState(EState::Dark);
	}
}

