// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartForPlanet.h"

// Sets default values
APlayerStartForPlanet::APlayerStartForPlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	isFree = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(RootScene);

	SpawnPoint->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

}

// Called when the game starts or when spawned
void APlayerStartForPlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerStartForPlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

