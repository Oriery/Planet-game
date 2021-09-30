// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWithPlanetGravity.h"

// Sets default values
AActorWithPlanetGravity::AActorWithPlanetGravity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisibleMesh->SetupAttachment(RootComponent);

	VisibleMesh->SetSimulatePhysics(true);
	VisibleMesh->SetEnableGravity(false);

}

// Called when the game starts or when spawned
void AActorWithPlanetGravity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorWithPlanetGravity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

