// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthPlayerController.h"
#include "LuxLabyrinth/LuxLabyrinthCharacter.h"
#include "Blueprint/UserWidget.h"
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

	MenuWidget = CreateWidget<UUserWidget>(this, MenuWidgetClass);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
		MenuWidget->SetVisibility(ESlateVisibility::Hidden);
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

		//** Toggle menu **//
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Triggered, this, &ALuxLabyrinthPlayerController::ToggleMenuTriggered);
	}
}

void ALuxLabyrinthPlayerController::Move(const FInputActionValue& Value)
{
	if (!bIsInputEnabled) return;

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

		if (MovementVector.Y > 0 && !bHasMovedForward)
		{
			OnMoveForward.Broadcast();
			bHasMovedForward = true;
		}
		else if (MovementVector.Y < 0 && !bHasMovedBackward)
		{
			OnMoveBackward.Broadcast();
			bHasMovedBackward = true;
		}
		if (MovementVector.X > 0 && !bHasMovedRight)
		{
			OnMoveRight.Broadcast();
			bHasMovedRight = true;
		}
		else if (MovementVector.X < 0 && !bHasMovedLeft)
		{
			OnMoveLeft.Broadcast();
			bHasMovedLeft = true;
		}
	}
}

void ALuxLabyrinthPlayerController::Look(const FInputActionValue& Value)
{
	if (!bIsInputEnabled) return;

	ALuxLabyrinthCharacter* LuxLabyrinthCharacter = Cast<ALuxLabyrinthCharacter>(GetPawn());

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (LuxLabyrinthCharacter != nullptr)
	{
		// add yaw and pitch input to controller
		LuxLabyrinthCharacter->AddControllerYawInput(LookAxisVector.X);
		LuxLabyrinthCharacter->AddControllerPitchInput(LookAxisVector.Y);

		if (LookAxisVector.X != 0 && LookAxisVector.Y != 0 && !bHasLooked)
		{
			OnLook.Broadcast();
			bHasLooked = true;
		}
	}
}

void ALuxLabyrinthPlayerController::JumpTriggered()
{
	if (!bIsInputEnabled) return;

	if (!bHasJumped)
	{
		OnJump.Broadcast();
		bHasJumped = true;
	}
	GetCharacter()->Jump();
}

void ALuxLabyrinthPlayerController::JumpReleased()
{
	GetCharacter()->StopJumping();
}

void ALuxLabyrinthPlayerController::ToggleMenuTriggered()
{
	if (MenuWidget)
	{
		if (MenuWidget->IsVisible())
		{
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
			// Enable game-only input mode
			FInputModeGameOnly InputModeData;
			SetInputMode(InputModeData);

			// Hide mouse cursor
			this->bShowMouseCursor = false;

			// Enable character movement and look
			ALuxLabyrinthCharacter* LuxCharacter = Cast<ALuxLabyrinthCharacter>(GetPawn());
			if (LuxCharacter)
			{
				bIsInputEnabled = true;
			}
			OnToggleMenu.Broadcast();
		}
		else
		{
			MenuWidget->SetVisibility(ESlateVisibility::Visible);
			// Enable game and UI input mode
			FInputModeGameAndUI InputModeData;
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputModeData.SetWidgetToFocus(MenuWidget->TakeWidget());
			SetInputMode(InputModeData);

			// Show mouse cursor
			this->bShowMouseCursor = true;

			// Disable character movement and look
			ALuxLabyrinthCharacter* LuxCharacter = Cast<ALuxLabyrinthCharacter>(GetPawn());
			if (LuxCharacter)
			{
				bIsInputEnabled = false;
			}
			OnToggleMenu.Broadcast();
		}
	}
}
