// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_SolidWall.h"

// Sets default values
ARhino_SolidWall::ARhino_SolidWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_SolidWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhino_SolidWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

