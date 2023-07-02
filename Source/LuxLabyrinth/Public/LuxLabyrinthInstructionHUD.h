// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LuxLabyrinthInstructionHUD.generated.h"

//class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class LUXLABYRINTH_API ULuxLabyrinthInstructionHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* MoveForwardInstructionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* MoveBackwardInstructionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* MoveLeftInstructionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* MoveRightInstructionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* LookInstructionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* JumpInstructionText;

	UFUNCTION()
	void OnMoveForwardInstructionCompleted();

	UFUNCTION()
	void OnMoveBackwardInstructionCompleted();

	UFUNCTION()
	void OnMoveLeftInstructionCompleted();

	UFUNCTION()
	void OnMoveRightInstructionCompleted();
	
	UFUNCTION()
	void OnLookInstructionCompleted();

	UFUNCTION()
	void OnJumpInstructionCompleted();
};
