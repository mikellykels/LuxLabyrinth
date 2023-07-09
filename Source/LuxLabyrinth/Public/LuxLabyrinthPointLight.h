// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuxLabyrinthPointLight.generated.h"

class UPointLightComponent;
class USceneComponent;

UCLASS()
class LUXLABYRINTH_API ALuxLabyrinthPointLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuxLabyrinthPointLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to light up the light
	UFUNCTION(BlueprintCallable, Category = "Light")
	FTimerHandle LightUp();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* PointLight;

	// Whether the light is lit or not
	bool bIsLit;

};
