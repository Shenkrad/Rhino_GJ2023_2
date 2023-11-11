// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rhino_GJ2023Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "Objects/Rhino_BreakableWall.h"
#include "Objects/Rhino_Fruit.h"
#include "Objects/Rhino_Door.h"
#include "Rhino_GJ2023GameMode.h"

ARhino_GJ2023Character::ARhino_GJ2023Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxCollisionComponent->SetupAttachment(RootComponent);
}

void ARhino_GJ2023Character::BeginPlay()
{
	Super::BeginPlay();

	// Binding collision
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARhino_GJ2023Character::OnBoxCollisionBeginOverlap);

	//Get ref to GameMode
	if (!GameMode)
	{
		GameMode = Cast<ARhino_GJ2023GameMode>(GetWorld()->GetAuthGameMode());
	}

	//Set DashCount to Max
	UpdateDashCount(MaxDashCount);
	//Set KillCount to 0
	UpdateKillCount(0);
}

void ARhino_GJ2023Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ARhino_GJ2023Character:: OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ARhino_BreakableWall* BreakableWall = Cast<ARhino_BreakableWall>(OtherActor);
	
	if (BreakableWall != nullptr && bIsDashing)
	{
		BreakableWall->DestroyWall();
	}

	ARhino_Fruit* Fruit = Cast<ARhino_Fruit>(OtherActor);

	if (Fruit != nullptr)
	{
		Fruit->CollectFruit();
		UpdateDashCount(1);
	}

	ARhino_Door* Door = Cast<ARhino_Door>(OtherActor);
	if (Door != nullptr)
	{
		Door->Request_WinCheck();
	}
}

void ARhino_GJ2023Character::SetIsDashing(bool IsDashing)
{
	bIsDashing = IsDashing;
}

bool ARhino_GJ2023Character::GetIsDashing() const
{
	return bIsDashing;
}

void ARhino_GJ2023Character::UpdateDashCount(int32 AddDash)
{
	if (DashCount + AddDash < 0)
		return;
	else if (DashCount + AddDash > MaxDashCount)
		return;

	DashCount += AddDash;
	if (GameMode)
	{
		GameMode->SetDashCountUI(DashCount, MaxDashCount);
	}
}
void ARhino_GJ2023Character::UpdateKillCount(int32 AddKill)
{
	if (KillCount + AddKill < 0)
		return;

	KillCount += AddKill;
	if (GameMode)
	{
		GameMode->SetKillCountUI(KillCount);
	}
}
