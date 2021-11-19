// Fill out your copyright notice in the Description page of Project Settings.


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, text);

#include "ActorWithPlanetGravity.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AActorWithPlanetGravity::AActorWithPlanetGravity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	VisibleMesh->SetSimulatePhysics(true);
	VisibleMesh->SetEnableGravity(false);

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AActorWithPlanetGravity::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (ActorOfCenterOfGravity)
		{
			LocationOfCenterOfGravity = ActorOfCenterOfGravity->GetActorLocation();
		}
		else
		{
			LocationOfCenterOfGravity = FVector(0.f, 0.f, 0.f);
		}
		
	}
}

// Called every frame
void AActorWithPlanetGravity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector vec = (GetActorLocation() - LocationOfCenterOfGravity);
		vec.Normalize();
		VisibleMesh->SetPhysicsLinearVelocity(- vec * 2, true);
	}
}

