// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_NPCAIController.h"

void ARhino_NPCAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
    }
}

void ARhino_NPCAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

