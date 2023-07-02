// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "LuxLabyrinthPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveForwardSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveBackwardSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveLeftSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveRightSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLookSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpSignature);

/**
 * 
 */
UCLASS()
class LUXLABYRINTH_API ALuxLabyrinthPlayerController : public APlayerController
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnMoveForwardSignature OnMoveForward;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnMoveForwardSignature OnMoveBackward;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnMoveLeftSignature OnMoveLeft;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnMoveRightSignature OnMoveRight;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnLookSignature OnLook;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnJumpSignature OnJump;

	bool bHasMovedForward = false;
	bool bHasMovedBackward = false;
	bool bHasMovedLeft = false;
	bool bHasMovedRight = false;
	bool bHasLooked = false;
	bool bHasJumped = false;

protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for jump input */
	void JumpTriggered();
	void JumpReleased();
};
