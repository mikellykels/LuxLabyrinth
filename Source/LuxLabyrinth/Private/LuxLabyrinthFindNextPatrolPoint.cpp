// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthFindNextPatrolPoint.h"
#include "LuxLabyrinthShadowCharacterAI.h"
#include "LuxLabyrinthShadowAIController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ULuxLabyrinthFindNextPatrolPoint::ULuxLabyrinthFindNextPatrolPoint()
{
}

EBTNodeResult::Type ULuxLabyrinthFindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	ALuxLabyrinthShadowCharacterAI* Shadow = Cast<ALuxLabyrinthShadowCharacterAI>(AIController->GetPawn());

	if (!Shadow || Shadow->PatrolPoints.Num() == 0)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();

	int32 Index = BlackboardComp->GetValueAsInt("PatrolPointIndex");
	Index++;
	if (Index >= Shadow->PatrolPoints.Num())
	{
		Index = 0;
	}
	BlackboardComp->SetValueAsInt("PatrolPointIndex", Index);

	ALuxLabyrinthPatrolPoint* NextPoint = Shadow->PatrolPoints[Index];
	BlackboardComp->SetValueAsObject("CurrentPatrolPoint", NextPoint);
	return EBTNodeResult::Succeeded;
}
