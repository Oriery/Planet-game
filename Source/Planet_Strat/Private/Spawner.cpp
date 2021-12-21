// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::mainAction()
{
	FActorSpawnParameters param = FActorSpawnParameters();
	param.bNoFail = true;
	if (WhatToSpawn)
	{
		AActor* spawnedActor = GetWorld()->SpawnActor(WhatToSpawn, &GetTransform(), param);
	}
	else
	{
		print("Class of WhatToSpawn not defined in Spawner");
	}
}

