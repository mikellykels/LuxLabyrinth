// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LuxLabyrinthFindNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class LUXLABYRINTH_API ULuxLabyrinthFindNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	ULuxLabyrinthFindNextPatrolPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
