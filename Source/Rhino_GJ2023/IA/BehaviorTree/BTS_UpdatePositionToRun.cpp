// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdatePositionToRun.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Rhino_NPCAIController.h"

UBTS_UpdatePositionToRun::UBTS_UpdatePositionToRun()
{
    NodeName = TEXT("Update Position to Run");
}

void UBTS_UpdatePositionToRun::OnGameplayTaskActivated(class UGameplayTask& Task)
{
    // Implement if needed
}

void UBTS_UpdatePositionToRun::OnGameplayTaskDeactivated(class UGameplayTask& Task)
{
    // Implement if needed
}

void UBTS_UpdatePositionToRun::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ARhino_NPCAIController* AIController = Cast<ARhino_NPCAIController>(OwnerComp.GetAIOwner());
    if (AIController == nullptr) return;

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if (PlayerPawn == nullptr) return;
    
    FVector AIPosition = AIController->GetPawn()->GetActorLocation();
    FVector PlayerPosition = PlayerPawn->GetActorLocation();

    FVector DirectionToPlayer = PlayerPosition - AIPosition;
    DirectionToPlayer.Normalize();
    
    FVector NewAIPosition = AIPosition -DirectionToPlayer * AIController->DistanceToMove;

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NewAIPosition);
}

