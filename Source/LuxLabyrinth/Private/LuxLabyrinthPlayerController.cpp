// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthPlayerController.h"
#include "LuxLabyrinth/LuxLabyrinthCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ALuxLabyrinthPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ALuxLabyrinthPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//** Moving **//
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALuxLabyrinthPlayerController::Move);

		//** Looking **//
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALuxLabyrinthPlayerController::Look);

		// ** Jumping ** //
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALuxLabyrinthPlayerController::JumpTriggered);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ALuxLabyrinthPlayerController::JumpReleased);
	}
}

void ALuxLabyrinthPlayerController::Move(const FInputActionValue& Value)
{
	ALuxLabyrinthCharacter* LuxLabyrinthCharacter = Cast<ALuxLabyrinthCharacter>(GetPawn());

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (LuxLabyrinthCharacter != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = LuxLabyrinthCharacter->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		LuxLabyrinthCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
		LuxLabyrinthCharacter->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ALuxLabyrinthPlayerController::Look(const FInputActionValue& Value)
{
	ALuxLabyrinthCharacter* LuxLabyrinthCharacter = Cast<ALuxLabyrinthCharacter>(GetPawn());

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (LuxLabyrinthCharacter != nullptr)
	{
		// add yaw and pitch input to controller
		LuxLabyrinthCharacter->AddControllerYawInput(LookAxisVector.X);
		LuxLabyrinthCharacter->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALuxLabyrinthPlayerController::JumpTriggered()
{
	GetCharacter()->Jump();
}

void ALuxLabyrinthPlayerController::JumpReleased()
{
	GetCharacter()->StopJumping();
}