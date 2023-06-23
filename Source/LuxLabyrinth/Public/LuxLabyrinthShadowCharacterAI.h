// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LuxLabyrinthPatrolPoint.h"
#include "LuxLabyrinthShadowCharacterAI.generated.h"

class UBoxComponent;

UCLASS()
class LUXLABYRINTH_API ALuxLabyrinthShadowCharacterAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALuxLabyrinthShadowCharacterAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	UBoxComponent* BoxCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Points")
	TArray<ALuxLabyrinthPatrolPoint*> PatrolPoints;
};
