// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_GenericWall.h"

// Sets default values
ARhino_GenericWall::ARhino_GenericWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_GenericWall::BeginPlay()
{
	Super::BeginPlay();

	if (Model == nullptr)
	{
		Model = FindComponentByClass<UStaticMeshComponent>();
	}
	
	DeSpawnWall();
}

// Called every frame
void ARhino_GenericWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARhino_GenericWall::SpawnWall()
{
	if (Model)
	{
		Model->Activate();
		Model->SetVisibility(true, true);
		Model->SetCollisionProfileName(FName(TEXT("BlockAll")));
		
	}
}

void ARhino_GenericWall::DeSpawnWall()
{
	if (Model)
	{
		Model->SetVisibility(false, true);
		Model->SetCollisionProfileName(FName(TEXT("NoCollision")));
		Model->Deactivate();
	}
}

void ARhino_GenericWall::DestroyWall()
{
	DeSpawnWall();
}