// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Rhino_Pickable.h"

#include "Rhino_Fruit.generated.h"


UCLASS()
class RHINO_GJ2023_API ARhino_Fruit : public ARhino_Pickable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhino_Fruit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void SpawnFruit();
	UFUNCTION()
	void DeSpawnFruit();
	UFUNCTION(BlueprintCallable)
	void CollectFruit();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
