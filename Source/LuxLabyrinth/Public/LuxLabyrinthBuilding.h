// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuxLabyrinthBuilding.generated.h"

class UPointLightComponent;
class USceneComponent;

UCLASS()
class LUXLABYRINTH_API ALuxLabyrinthBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuxLabyrinthBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to light up the building
	UFUNCTION(BlueprintCallable, Category = "Building")
	FTimerHandle LightUp();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* PointLight;

	// Whether the building is lit or not
	bool bIsLit;
};
