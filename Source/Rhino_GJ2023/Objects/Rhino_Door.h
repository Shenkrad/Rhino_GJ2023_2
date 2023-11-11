// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rhino_Door.generated.h"

UCLASS()
class RHINO_GJ2023_API ARhino_Door : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARhino_Door();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY()
	UStaticMeshComponent* Model;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnDoor();
	UFUNCTION(BlueprintCallable)
	virtual void DeSpawnDoor();
	UFUNCTION(BlueprintCallable)
	virtual void Request_WinCheck();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
