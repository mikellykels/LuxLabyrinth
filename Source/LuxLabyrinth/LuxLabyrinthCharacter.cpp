// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuxLabyrinthCharacter.h"
#include "LuxLabyrinthHoop.h"
#include "LuxLabyrinthHoopCountHUD.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


//////////////////////////////////////////////////////////////////////////
// ALuxLabyrinthCharacter

ALuxLabyrinthCharacter::ALuxLabyrinthCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 55.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a point light and attach it to the root component
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);

	// By default, the point light should be off since the default state is dark
	PointLight->SetVisibility(false, true);
}

void ALuxLabyrinthCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Subscribe to hoop activation events
	for (TActorIterator<ALuxLabyrinthHoop> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ActorItr->OnHoopActivated.AddDynamic(this, &ALuxLabyrinthCharacter::OnHoopActivated);
	}
}

void ALuxLabyrinthCharacter::SetState(EState NewState)
{
	CurrentState = NewState;

	switch (CurrentState)
	{
	case EState::Light:
		PointLight->SetVisibility(true, true);
		break;
	case EState::Dark:
		PointLight->SetVisibility(false, true);
		break;
	}
}

void ALuxLabyrinthCharacter::OnHoopActivated()
{
	SetState(EState::Light);
}

float ALuxLabyrinthCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	FString TheFloatStr = FString::SanitizeFloat(ActualDamage);
	if (ActualDamage > 0.f)
	{
		if (!bIsInvincible)
		{
			bIsInvincible = true;
			Health -= ActualDamage;

			// Make sure the new health value stays in the range between zero and max health.
			Health = FMath::Clamp(Health, 0.0f, MaxHealth);
			if (Health < 0)
			{
				Health = 0;
			}
			GetWorldTimerManager().SetTimer(InvincibilityTimer, this, &ALuxLabyrinthCharacter::EndInvincibility, 2.0f, false);
		
			OnHealthChanged.Broadcast(Health);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation(), GetActorRotation());
		}
	}

	return ActualDamage;
}

void ALuxLabyrinthCharacter::EndInvincibility()
{
	bIsInvincible = false;
}

