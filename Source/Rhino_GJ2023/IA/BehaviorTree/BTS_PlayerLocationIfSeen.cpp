// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_PlayerLocationIfSeen::UBTS_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTS_PlayerLocationIfSeen::OnGameplayTaskActivated(class UGameplayTask& Task)
{
    // Implement if needed
}

void UBTS_PlayerLocationIfSeen::OnGameplayTaskDeactivated(class UGameplayTask& Task)
{
    // Implement if needed
}

void UBTS_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if (PlayerPawn == nullptr) return;
    if (OwnerComp.GetAIOwner() == nullptr) return;

    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

