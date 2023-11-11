// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_Door.h"
#include "Rhino_GJ2023/Rhino_GJ2023GameMode.h"

// Sets default values
ARhino_Door::ARhino_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_Door::BeginPlay()
{
	Super::BeginPlay();

	if (Model == nullptr)
	{
		Model = FindComponentByClass<UStaticMeshComponent>();
	}
	DeSpawnDoor();
}

// Called every frame
void ARhino_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARhino_Door::SpawnDoor()
{
	if (Model)
	{
		Model->Activate();
		Model->SetVisibility(true, true);
		Model->SetCollisionProfileName(FName(TEXT("BlockAll")));
		
	}
}

void ARhino_Door::DeSpawnDoor()
{
	if (Model)
	{
		Model->SetVisibility(false, true);
		Model->SetCollisionProfileName(FName(TEXT("OverlapAll")));
		//Model->Deactivate();
	}
}

void ARhino_Door::Request_WinCheck()
{
	if (ARhino_GJ2023GameMode* GameMode = Cast<ARhino_GJ2023GameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->Check_WinCondition(this);
	}
}