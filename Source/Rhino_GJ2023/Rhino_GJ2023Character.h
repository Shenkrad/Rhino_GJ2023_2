// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Rhino_GJ2023Character.generated.h"

class UBoxComponent;
class ARhino_GJ2023GameMode;

UCLASS(Blueprintable)
class ARhino_GJ2023Character : public ACharacter
{
	GENERATED_BODY()

public:
	ARhino_GJ2023Character();

	virtual void BeginPlay();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerDashAnimation();

	void SetIsDashing(bool IsDashing);
	bool GetIsDashing() const;

	int32 GetDashCount() { return DashCount; };
	int32 GetMaxDashCount() { return MaxDashCount; };
	int32 GetMaxKillCount() { return KillCount; }

	
	void SetDashCount(int32 Count) { this->DashCount = Count; };
	void SetKillCount(int32 Count) { this->KillCount = Count; };


	/*
	* Always use this to value check && update UI
	* If Add value is negative, it subtracts
	* Safe checks new value
	*/
	void UpdateDashCount(int32 AddDash);
	/*
	* Always use this to value check && update UI
	* If Add value is negative, it subtracts
	* Safe checks new value
	*/
	void UpdateKillCount(int32 AddKill);

	UFUNCTION(BlueprintCallable)
	int32 GetKillCount() { return KillCount; };

private:


	/*DASH AND KILL MECHANICS VARIABLES*/
	UPROPERTY()
	bool bIsDashing = false;
	UPROPERTY()
	int32 DashCount = 0;
	UPROPERTY(EditAnywhere, Category = "Dash Mechanic")
	int32 MaxDashCount = 3;

	UPROPERTY()
	int32 KillCount = 0;

	UPROPERTY()
	ARhino_GJ2023GameMode* GameMode;


	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/* Box componet to check dash collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollisionComponent;

	UFUNCTION()
	void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};

