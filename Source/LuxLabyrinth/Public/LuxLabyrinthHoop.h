// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuxLabyrinthHoop.generated.h"

class ALuxLabyrinthBuilding;
class ALuxLabyrinthPointLight;
class ALuxLabyrinthStreetLightPost;
class UBoxComponent;
class USoundCue;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoopActivatedSignature);

UCLASS()
class LUXLABYRINTH_API ALuxLabyrinthHoop : public AActor
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HoopMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hoop", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;
	
public:	
	// Sets default values for this actor's properties
	ALuxLabyrinthHoop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// whether hoop has been activated before
	bool bHasBeenActivated = false;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* CollectSound = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// function to be called when Lux passes through hoop
	UFUNCTION()
	void OnPassedThrough(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Binding event for hoop activation
	UPROPERTY(BlueprintAssignable, Category = "Hoop")
	FOnHoopActivatedSignature OnHoopActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
	TArray<ALuxLabyrinthBuilding*> Buildings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Posts")
	TArray<ALuxLabyrinthStreetLightPost*> LightPosts;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point Lights")
	TArray<ALuxLabyrinthPointLight*> PointLights;

private:
	int32 CurrentBuildingIndex;
	int32 CurrentLightPostIndex;
	int32 CurrentPointLightIndex;

	void LightUpNextBuilding();
	void LightUpNextLight();
	void LightUpNextPointLight();
};
