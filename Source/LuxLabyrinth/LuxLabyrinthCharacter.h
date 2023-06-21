// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LuxLabyrinthCharacter.generated.h"

class UCameraComponent;
class UInputComponent;
class UPointLightComponent;
class UStaticMeshComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum class EState : uint8
{
	Light     UMETA(DisplayName = "Light"),
	Dark      UMETA(DisplayName = "Dark")
};

UCLASS(config=Game)
class ALuxLabyrinthCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lux", meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* PointLight;

public:
	ALuxLabyrinthCharacter();
			
protected:
	virtual void BeginPlay();

public:
	/** Get current state **/
	UFUNCTION(BlueprintPure, Category = "Lux")
	EState GetCurrentState() const
	{
		return CurrentState;
	}

	//** Set state **/
	UFUNCTION(BlueprintCallable, Category = "Lux")
	void SetState(EState NewState);

	UFUNCTION()
	void OnHoopActivated();

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	EState CurrentState = EState::Dark;
};

