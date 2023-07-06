// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuxLabyrinthHealthCrate.generated.h"

class ALuxLabyrinthCharacter;
class USoundCue;
class USphereComponent;
class UWidgetComponent;

UCLASS()
class LUXLABYRINTH_API ALuxLabyrinthHealthCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuxLabyrinthHealthCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The amount of health that this health kit gives
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float HealthAmount = 10.f;

	// Called when the player overlaps with this actor
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Collision")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* CollectSound = nullptr;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 50.0f;

private:
	ALuxLabyrinthCharacter* PlayerCharacter;
};
