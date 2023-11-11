// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rhino_GenericWall.generated.h"

UCLASS()
class RHINO_GJ2023_API ARhino_GenericWall : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARhino_GenericWall();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY()
	UStaticMeshComponent* Model;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnWall();
	UFUNCTION(BlueprintCallable)
	virtual void DeSpawnWall();
	UFUNCTION(BlueprintCallable)
	virtual void DestroyWall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
