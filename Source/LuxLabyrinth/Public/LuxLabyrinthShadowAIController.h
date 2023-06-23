// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LuxLabyrinthShadowAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class LUXLABYRINTH_API ALuxLabyrinthShadowAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALuxLabyrinthShadowAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	TArray<AActor*> PatrolPoints;
	
};
