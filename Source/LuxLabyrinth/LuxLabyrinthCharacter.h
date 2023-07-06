// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LuxLabyrinthCharacter.generated.h"

class UCameraComponent;
class UInputComponent;
class UParticleSystem;
class UPointLightComponent;
class USoundCue;
class UStaticMeshComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangedSignature, float, Health);

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

	// set default health value to 100
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 100.0f;

	// set default max health value to 100
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	// set damage taken per hit by enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float DamagePerHit = 10.0f;

	void AddHealth(float Amount);

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FHealthChangedSignature OnHealthChanged;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, Category = "FX")
	UParticleSystem* HitFX;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* HitSound = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lux")
	bool bIsInvincible = false;

	FTimerHandle InvincibilityTimer;

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	EState CurrentState = EState::Dark;

	void EndInvincibility();
};

