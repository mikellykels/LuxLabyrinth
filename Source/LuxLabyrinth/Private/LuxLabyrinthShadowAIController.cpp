// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxLabyrinthShadowAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ALuxLabyrinthShadowAIController::ALuxLabyrinthShadowAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialie PerceptionComponent
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	// Setup SightConfig parameters
	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 9.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// Initialize BehaviorTree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_Object(TEXT("/Game/AI/BehaviorTree"));
	if (BT_Object.Succeeded())
	{
		BehaviorTree = BT_Object.Object;
	}
}

void ALuxLabyrinthShadowAIController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), PatrolPoints);
}

void ALuxLabyrinthShadowAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		// Initialize BlackboardComponent and start the behavior tree
		BlackboardComponent = GetBlackboardComponent();
		RunBehaviorTree(BehaviorTree);
	}
}

void ALuxLabyrinthShadowAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
