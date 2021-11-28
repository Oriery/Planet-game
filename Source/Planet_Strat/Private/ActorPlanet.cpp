// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPlanet.h"

// Sets default values
AActorPlanet::AActorPlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//RootComponent = VisibleMesh;

	VisibleMesh->SetCollisionProfileName("Custom...");
	VisibleMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic); // �� �������� (������ � Blueprint)
	VisibleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore); // �� �������� (������ � Blueprint)

}

// Called when the game starts or when spawned
void AActorPlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorPlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

