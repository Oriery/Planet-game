// Fill out your copyright notice in the Description page of Project Settings.


#include "LabelOfTeams.h"

// Sets default values
ALabelOfTeams::ALabelOfTeams()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	DeltaHeight = 10;
	RotationSpeed = 20;
	HeightFrequency = 1;
}

// Called when the game starts or when spawned
void ALabelOfTeams::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalLocation = GetActorLocation();
}

// Called every frame
void ALabelOfTeams::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority())
	{
		FVector NewLocation = OriginalLocation;
		NewLocation += GetActorUpVector() * FMath::Sin(GetGameTimeSinceCreation() * HeightFrequency) * DeltaHeight;
		SetActorLocation(NewLocation);
		AddActorLocalRotation(FRotator(0, DeltaTime * RotationSpeed, 0));
	}
}

