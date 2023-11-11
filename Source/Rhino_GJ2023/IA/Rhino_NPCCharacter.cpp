// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_NPCCharacter.h"

#include "Components/CapsuleComponent.h"
#include "../Rhino_GJ2023Character.h"

// Sets default values
ARhino_NPCCharacter::ARhino_NPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_NPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ARhino_NPCCharacter::OnCapsuleHit);
	
}

// Called every frame
void ARhino_NPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARhino_NPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called when Capsule Component hits
void ARhino_NPCCharacter::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ARhino_GJ2023Character* MainCharacter = Cast<ARhino_GJ2023Character>(OtherActor);
	if (MainCharacter == nullptr) return;

	Die(MainCharacter);
}

void ARhino_NPCCharacter::Die(ARhino_GJ2023Character* MainCharacter)
{	
	if (MainCharacter->GetIsDashing())
	{
		GetMesh()->SetSimulatePhysics(true);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();
	}
}

