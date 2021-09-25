// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube_Cpp.h"

// Sets default values
ACube_Cpp::ACube_Cpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisibleMesh->SetupAttachment(RootComponent);

	VisibleMesh->SetSimulatePhysics(true);
	VisibleMesh->SetEnableGravity(false);

}

// Called when the game starts or when spawned
void ACube_Cpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACube_Cpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

