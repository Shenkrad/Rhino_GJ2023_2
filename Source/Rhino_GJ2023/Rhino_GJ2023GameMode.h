// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Rhino_GJ2023GameMode.generated.h"


class ARhino_SolidWall;
class ARhino_BreakableWall;
class ARhino_Fruit;
class ARhino_Door;
class ARhino_HUD;

USTRUCT(BlueprintType)
struct FTimeFormat
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 Seconds = 0;
	UPROPERTY()
		int32 Minutes = 0;
	UPROPERTY()
		int32 Hours = 0;
};
UCLASS(minimalapi)
class ARhino_GJ2023GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARhino_GJ2023GameMode();

	UPROPERTY(EditAnywhere, Category = "MazeSpawn Options")
		int32 NumberSolidWalls = 5;
	UPROPERTY(EditAnywhere, Category = "MazeSpawn Options")
		int32 NumberBreakableWalls = 5;
	UPROPERTY(EditAnywhere, Category = "MazeSpawn Options")
		int32 NumberDoors = 1;
	UPROPERTY(EditAnywhere, Category = "MazeSpawn Options")
		int32 NumberFruits = 5;
	UPROPERTY(EditAnywhere, Category = "Fruits Options")
		float FruitTimeToRespawn = 2.5f;

	UFUNCTION(BlueprintCallable)
		void ScanAllObjects();
	UFUNCTION(BlueprintCallable)
		void RandomSpawnObjects();
	UFUNCTION()
		void RequestFruitRespawn(ARhino_Fruit* CollectedFruit); 
	UFUNCTION()
		void RequestWallDestroy(ARhino_BreakableWall* DestroyedWall);


	UFUNCTION()
		void SetDashCountUI(int32 DashCount, int32 MaxDashCount);
	UFUNCTION()
		void SetKillCountUI(int32 KillCount);

	UFUNCTION(BlueprintCallable)
		void Check_WinCondition(ARhino_Door* RequestingDoor);
	UFUNCTION()
		void Init_GameWin();


protected:

	UPROPERTY()
	TArray<ARhino_SolidWall*> ActiveSolidWalls;
	UPROPERTY()
	TArray<ARhino_BreakableWall*> ActiveBreakableWalls;
	UPROPERTY()
	TArray<ARhino_Fruit*> ActiveFruits;
	UPROPERTY()
	TArray<ARhino_Door*> ActiveDoors;
	UPROPERTY()
	TArray<ARhino_SolidWall*> InactiveSolidWalls;
	UPROPERTY()
	TArray<ARhino_BreakableWall*> InactiveBreakableWalls;
	UPROPERTY()
	TArray<ARhino_Fruit*> InactiveFruits;
	UPROPERTY()
	TArray<ARhino_Door*> InactiveDoors;


	virtual void BeginPlay() override;

	UFUNCTION()
	void FruitRespawn(ARhino_Fruit* CollectedFruit);

	UFUNCTION()
		void WallDestroy(ARhino_BreakableWall* DestroyedWall);


	UFUNCTION()
		void InitializeTimer();
	UFUNCTION()
		void SetUITimer();

	FTimeFormat Time;

	UPROPERTY()
		ARhino_HUD* HUD;

};



