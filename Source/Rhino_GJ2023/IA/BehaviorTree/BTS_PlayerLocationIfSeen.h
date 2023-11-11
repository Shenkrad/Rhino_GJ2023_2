// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_PlayerLocationIfSeen.generated.h"

/**
 *  Updates player info if is in line of sight and clears the value when it doesn't
 */
UCLASS()
class RHINO_GJ2023_API UBTS_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTS_PlayerLocationIfSeen();

	virtual void OnGameplayTaskActivated(class UGameplayTask& Task) override;

    virtual void OnGameplayTaskDeactivated(class UGameplayTask& Task) override;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
