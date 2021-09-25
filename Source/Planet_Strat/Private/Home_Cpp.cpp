// Fill out your copyright notice in the Description page of Project Settings.


#include "Home_Cpp.h"

// Sets default values
AHome_Cpp::AHome_Cpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisibleMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHome_Cpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHome_Cpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

