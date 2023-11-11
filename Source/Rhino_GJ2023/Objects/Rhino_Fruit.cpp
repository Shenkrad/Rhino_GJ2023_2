// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_Fruit.h"
#include "Rhino_GJ2023/Rhino_GJ2023GameMode.h"

// Sets default values
ARhino_Fruit::ARhino_Fruit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_Fruit::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh == nullptr)
	{
		Mesh = FindComponentByClass<UStaticMeshComponent>();
	}
}

// Called every frame
void ARhino_Fruit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARhino_Fruit::SpawnFruit()
{
	SpawnPickable();
}

void ARhino_Fruit::DeSpawnFruit()
{
	DeSpawnPickable();
}

void ARhino_Fruit::CollectFruit()
{
	DeSpawnPickable();

	if (GetWorld())
	{
		if (ARhino_GJ2023GameMode* GameMode = Cast<ARhino_GJ2023GameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->RequestFruitRespawn(this);
		}
	}
}
