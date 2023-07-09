// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthInstructionHUD.h"
#include "LuxLabyrinthPlayerController.h"
#include "Components/TextBlock.h"

void ULuxLabyrinthInstructionHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ALuxLabyrinthPlayerController* PC = GetWorld()->GetFirstPlayerController<ALuxLabyrinthPlayerController>();
	if (PC)
	{
		PC->OnMoveForward.AddDynamic(this, &ULuxLabyrinthInstructionHUD::OnMoveForwardInstructionCompleted);
		PC->OnMoveBackward.AddDynamic(this, &ULuxLabyrinthInstructionHUD::OnMoveBackwardInstructionCompleted);
		PC->OnMoveLeft.AddDynamic(this, &ULuxLabyrinthInstructionHUD::OnMoveLeftInstructionCompleted);
		PC->OnMoveRight.AddDynamic(this, &ULuxLabyrinthInstructionHUD::OnMoveRightInstructionCompleted);
		PC->OnLook.AddDynamic(this, &ULuxLabyrinthInstructionHUD::OnLookInstructionCompleted);
		PC->OnJump.AddDynamic(this, &ULuxLabyrinthInstructionHUD::OnJumpInstructionCompleted);
	}
}

void ULuxLabyrinthInstructionHUD::OnMoveForwardInstructionCompleted()
{
	if (MoveForwardInstructionText)
	{
		MoveForwardInstructionText->SetText(FText::FromString("to move forward"));
	}
}

void ULuxLabyrinthInstructionHUD::OnMoveBackwardInstructionCompleted()
{
	if (MoveBackwardInstructionText)
	{
		MoveBackwardInstructionText->SetText(FText::FromString("to move backward"));
	}
}

void ULuxLabyrinthInstructionHUD::OnMoveLeftInstructionCompleted()
{
	if (MoveLeftInstructionText)
	{
		MoveLeftInstructionText->SetText(FText::FromString("to move left"));
	}
}

void ULuxLabyrinthInstructionHUD::OnMoveRightInstructionCompleted()
{
	if (MoveRightInstructionText)
	{
		MoveRightInstructionText->SetText(FText::FromString("to move right"));
	}
}

void ULuxLabyrinthInstructionHUD::OnLookInstructionCompleted()
{
	if (LookInstructionText)
	{
		LookInstructionText->SetText(FText::FromString("to look around"));
	}
}

void ULuxLabyrinthInstructionHUD::OnJumpInstructionCompleted()
{
	if (JumpInstructionText)
	{
		JumpInstructionText->SetText(FText::FromString("to jump"));
	}
}
