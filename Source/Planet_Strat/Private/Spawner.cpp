// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetText(FText::FromString("Cooldown"));
	TextRender->SetupAttachment(SceneRoot);

	bIsNotOnCooldown = true;

	CooldownLength = 5;

	bReplicates = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		TextRender->SetVisibility(false);
	}
}

void ASpawner::EndOfCooldown()
{
	bIsNotOnCooldown = true;

	MulticastRPC_SetVisibilityOfTextRender(false);
}

void ASpawner::MulticastRPC_SetVisibilityOfTextRender_Implementation(bool bVisible)
{
	if (!HasAuthority())
	{
		TextRender->SetVisibility(bVisible);
	}
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
		if (bIsNotOnCooldown)
		{
			AActor* spawnedActor = GetWorld()->SpawnActor(WhatToSpawn, &GetTransform(), param);

			FTimerHandle timerHandle;

			GetWorldTimerManager().SetTimer(timerHandle, this, &ASpawner::EndOfCooldown, 1.0, false, CooldownLength);

			MulticastRPC_SetVisibilityOfTextRender(true);
			bIsNotOnCooldown = false;
		}
	}
	else
	{
		print("Class of WhatToSpawn not defined in Spawner");
	}
}

