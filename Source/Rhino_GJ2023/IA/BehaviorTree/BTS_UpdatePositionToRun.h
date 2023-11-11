// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_UpdatePositionToRun.generated.h"

/**
 * 
 */
UCLASS()
class RHINO_GJ2023_API UBTS_UpdatePositionToRun : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTS_UpdatePositionToRun();

	virtual void OnGameplayTaskActivated(class UGameplayTask& Task) override;

    virtual void OnGameplayTaskDeactivated(class UGameplayTask& Task) override;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
