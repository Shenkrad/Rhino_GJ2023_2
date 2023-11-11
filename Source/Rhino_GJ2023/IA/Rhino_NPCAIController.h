// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Rhino_NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class RHINO_GJ2023_API ARhino_NPCAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Distance to move when the AI character sees the player
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	float DistanceToMove = 200.f;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
	
};
