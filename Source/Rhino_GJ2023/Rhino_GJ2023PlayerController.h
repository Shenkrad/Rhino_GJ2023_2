// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Rhino_GJ2023PlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class ARhino_GJ2023Character;

UCLASS()
class ARhino_GJ2023PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARhino_GJ2023PlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	// /** Jump Input Action */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// class UInputAction* SetDestinationClickAction;

	/* Dash Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	// /* Keyboard Movement Input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* KeyboardMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement Settings", meta=(AllowPrivateAccess = "true"))
	float DashLaunchVelocity = 3000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement Settings", meta=(AllowPrivateAccess = "true"))
	float DashWindow = 1.f;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	// uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnDashTriggered();
	void CharacterMovement(const FInputActionValue &Value);

private:
	// FVector CachedDestination;
	
	FTimerHandle DashTimerHandle;

	// float FollowTime; // For how long it has been pressed

	UPROPERTY()
	ARhino_GJ2023Character* ControlledCharacter;

	UFUNCTION()
	void OnStopDashing();
};


