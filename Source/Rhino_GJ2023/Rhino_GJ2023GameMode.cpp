// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rhino_GJ2023GameMode.h"
#include "Rhino_GJ2023PlayerController.h"
#include "Rhino_GJ2023Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/Gameplaystatics.h"
#include "Misc/Timespan.h"
#include "Misc/Char.h"

#include "Objects/Rhino_BreakableWall.h"
#include "Objects/Rhino_SolidWall.h"
#include "Objects/Rhino_Door.h"
#include "Objects/Rhino_Fruit.h"

#include "UI/Rhino_HUD.h"

ARhino_GJ2023GameMode::ARhino_GJ2023GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARhino_GJ2023PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ARhino_GJ2023GameMode::BeginPlay()
{
	Super::BeginPlay();

	ScanAllObjects();
	RandomSpawnObjects();
	InitializeTimer();
}

void ARhino_GJ2023GameMode::ScanAllObjects()
{

	InactiveSolidWalls.Empty();
	InactiveBreakableWalls.Empty();
	InactiveFruits.Empty();
	InactiveDoors.Empty();

	TArray<AActor*> Generic;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARhino_SolidWall::StaticClass(), Generic);
	for (int i = 0; i < Generic.Num(); i++)
	{
		if (Generic.IsValidIndex(i) && Generic[i] != nullptr)
		{
			if (ARhino_SolidWall* Wall = Cast<ARhino_SolidWall>(Generic[i]))
			{
				Wall->DeSpawnWall();
				InactiveSolidWalls.Add(Wall);
			}
		}
	}

	Generic.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARhino_BreakableWall::StaticClass(), Generic);
	for (int i = 0; i < Generic.Num(); i++)
	{
		if (Generic.IsValidIndex(i) && Generic[i] != nullptr)
		{
			if (ARhino_BreakableWall* Wall = Cast<ARhino_BreakableWall>(Generic[i]))
			{
				Wall->DeSpawnWall();
				InactiveBreakableWalls.Add(Wall);
			}
		}
	}

	Generic.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARhino_Fruit::StaticClass(), Generic);
	for (int i = 0; i < Generic.Num(); i++)
	{
		if (Generic.IsValidIndex(i) && Generic[i] != nullptr)
		{
			if (ARhino_Fruit* Fruit = Cast<ARhino_Fruit>(Generic[i]))
			{
				Fruit->DeSpawnFruit();
				InactiveFruits.Add(Fruit);
			}
		}
	}

	Generic.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARhino_Door::StaticClass(), Generic);
	for (int i = 0; i < Generic.Num(); i++)
	{
		if (Generic.IsValidIndex(i) && Generic[i] != nullptr)
		{
			if (ARhino_Door* Door = Cast<ARhino_Door>(Generic[i]))
			{
				Door->DeSpawnDoor();
				InactiveDoors.Add(Door);
			}
		}
	}
}

void ARhino_GJ2023GameMode::RandomSpawnObjects()
{

	ActiveSolidWalls.Empty();
	ActiveBreakableWalls.Empty();
	ActiveFruits.Empty();
	ActiveDoors.Empty();

	for (int i = 0; i < NumberSolidWalls; i++)
	{
		if (InactiveSolidWalls.IsEmpty())
			break;

		int32 Seed = FMath::RandRange(0, InactiveSolidWalls.Num() - 1);
		if (InactiveSolidWalls.IsValidIndex(Seed) && InactiveSolidWalls[Seed] != nullptr)
		{
			InactiveSolidWalls[Seed]->SpawnWall();
			ActiveSolidWalls.Add(InactiveSolidWalls[Seed]);
			InactiveSolidWalls.RemoveAt(Seed);
		}
	}

	for (int i = 0; i < NumberBreakableWalls; i++)
	{
		if (InactiveBreakableWalls.IsEmpty())
			break;

		int32 Seed = FMath::RandRange(0, InactiveBreakableWalls.Num() - 1);
		if (InactiveBreakableWalls.IsValidIndex(Seed) && InactiveBreakableWalls[Seed] != nullptr)
		{
			InactiveBreakableWalls[Seed]->SpawnWall();
			ActiveBreakableWalls.Add(InactiveBreakableWalls[Seed]);
			InactiveBreakableWalls.RemoveAt(Seed);
		}
	}

	for (int i = 0; i < NumberFruits; i++)
	{
		if (InactiveFruits.IsEmpty())
			break;

		int32 Seed = FMath::RandRange(0, InactiveFruits.Num() - 1);
		if (InactiveFruits.IsValidIndex(Seed) && InactiveFruits[Seed] != nullptr)
		{
			InactiveFruits[Seed]->SpawnFruit();
			ActiveFruits.Add(InactiveFruits[Seed]);
			InactiveFruits.RemoveAt(Seed);
		}
	}

	for (int i = 0; i < NumberDoors; i++)
	{
		if (InactiveDoors.IsEmpty())
			break;

		int32 Seed = FMath::RandRange(0, InactiveDoors.Num() - 1);
		if (InactiveDoors.IsValidIndex(Seed) && InactiveDoors[Seed] != nullptr)
		{
			InactiveDoors[Seed]->SpawnDoor();
			ActiveDoors.Add(InactiveDoors[Seed]);
			InactiveDoors.RemoveAt(Seed);
		}
	}
}

void ARhino_GJ2023GameMode::RequestFruitRespawn(ARhino_Fruit* CollectedFruit)
{
	FTimerHandle TimerHandle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "FruitRespawn", CollectedFruit);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, FruitTimeToRespawn, false);
}

void ARhino_GJ2023GameMode::FruitRespawn(ARhino_Fruit* CollectedFruit)
{
	//Check if CurrentNum - Collected fruit allows for another Fruit
	if (ActiveFruits.Num() - 1 >= NumberFruits)
	{
		return;
	}
	if (InactiveFruits.Find(CollectedFruit) > INDEX_NONE)
	{
		return;
	}

	int32 Seed = FMath::RandRange(0, InactiveFruits.Num() - 1);
	if (InactiveFruits.IsValidIndex(Seed) && InactiveFruits[Seed] != nullptr)
	{

		InactiveFruits[Seed]->SpawnFruit();
		ActiveFruits.Add(InactiveFruits[Seed]);
		InactiveFruits.RemoveAt(Seed);
	}
	ActiveFruits.Remove(CollectedFruit);
	InactiveFruits.Add(CollectedFruit);
}

void ARhino_GJ2023GameMode::RequestWallDestroy(ARhino_BreakableWall* DestroyedWall)
{
	WallDestroy(DestroyedWall);
}

void ARhino_GJ2023GameMode::WallDestroy(ARhino_BreakableWall* DestroyedWall)
{
	if (InactiveBreakableWalls.Find(DestroyedWall) > INDEX_NONE)
	{
		return;
	}
	ActiveBreakableWalls.Remove(DestroyedWall);
	InactiveBreakableWalls.Add(DestroyedWall);
}

void ARhino_GJ2023GameMode::InitializeTimer()
{
	if (HUD == nullptr)
	{
		HUD = Cast<ARhino_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARhino_GJ2023GameMode::SetUITimer, 1.f, true);
}

void ARhino_GJ2023GameMode::SetUITimer()
{
	Time.Seconds += 1;
	if (Time.Seconds >= 60)
	{
		Time.Seconds = 0;
		Time.Minutes += 1;
	}
	if (Time.Minutes >= 60)
	{
		Time.Minutes = 0;
		Time.Hours += 1;
	}

	if (HUD)
	{
		FString Seconds = FString::Printf(TEXT("%02i"), FMath::Abs(Time.Seconds));
		FString Minutes = FString::Printf(TEXT("%02i"), FMath::Abs(Time.Minutes));
		FString Hours = FString::Printf(TEXT("%02i"), FMath::Abs(Time.Hours));
		FString Format = FString::Printf(TEXT("%s:%s:%s"), *Hours, *Minutes, *Seconds);
		HUD->SetTimer(Format);
	}
}

void ARhino_GJ2023GameMode::SetDashCountUI(int32 DashCount, int32 MaxCount)
{
	if (HUD)
	{
		FString Format = FString::Printf(TEXT("Dash: %02i/%02i"), FMath::Abs(DashCount), FMath::Abs(MaxCount));
		HUD->SetDashCount(Format);
	}
}

void ARhino_GJ2023GameMode::SetKillCountUI(int32 KillCount)
{
	if (HUD)
	{
		FString Format = FString::Printf(TEXT("Kills: %02i"), FMath::Abs(KillCount));
		HUD->SetKillCount(Format);
	}
}

void ARhino_GJ2023GameMode::Check_WinCondition(ARhino_Door* RequestingDoor)
{
	for (int i = 0; i < ActiveDoors.Num(); i++)
	{
		if (ActiveDoors.IsValidIndex(i) && ActiveDoors[i])
		{
			if (ActiveDoors[i] == RequestingDoor)
				Init_GameWin();
		}
	}
}

void ARhino_GJ2023GameMode::Init_GameWin()
{
	ResetLevel();
}