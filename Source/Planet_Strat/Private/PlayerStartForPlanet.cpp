// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartForPlanet.h"

// Sets default values
APlayerStartForPlanet::APlayerStartForPlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(SceneRoot);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	team = ETeams::TEAM_A;
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

