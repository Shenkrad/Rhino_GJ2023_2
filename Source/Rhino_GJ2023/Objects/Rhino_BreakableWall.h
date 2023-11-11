// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Rhino_GenericWall.h"

#include "Rhino_BreakableWall.generated.h"

UCLASS()
class RHINO_GJ2023_API ARhino_BreakableWall : public ARhino_GenericWall
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhino_BreakableWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DestroyWall() override;

};
