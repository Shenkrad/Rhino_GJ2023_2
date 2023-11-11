// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_Pickable.h"


// Sets default values
ARhino_Pickable::ARhino_Pickable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_Pickable::BeginPlay()
{
	Super::BeginPlay();

	if (Model == nullptr)
	{
		Model = FindComponentByClass<UStaticMeshComponent>();
	}
	
	DeSpawnPickable();
}

// Called every frame
void ARhino_Pickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARhino_Pickable::SpawnPickable()
{
	if (Model)
	{
		Model->Activate();
		Model->SetVisibility(true, true);
		Model->SetCollisionProfileName(FName(TEXT("OverlapAll")));

		int32 Seed = FMath::RandRange(0, Pickables.Num() - 1);
		if (Pickables.IsValidIndex(Seed) && Pickables[Seed])
		{
			if (Model)
				Model->SetStaticMesh(Pickables[Seed]);
		}
	}
}

void ARhino_Pickable::DeSpawnPickable()
{
	if (Model)
	{
		Model->SetVisibility(false, true);
		Model->SetCollisionProfileName(FName(TEXT("NoCollision")));
		Model->Deactivate();
	}
}

void ARhino_Pickable::CollectPickable()
{
	
}

