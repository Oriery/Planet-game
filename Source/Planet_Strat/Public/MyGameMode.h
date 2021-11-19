// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerStartForPlanet.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLANET_STRAT_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	AMyGameMode();

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);

	UPROPERTY()
		TArray<APlayerStartForPlanet*> Spawners;

	UPROPERTY()
		AActor* ActorOfCenterOfGravity;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> DefaultGravityActor; // Planet Class

	UPROPERTY(EditAnywhere)
		float RadiusOfPlanet;

	UPROPERTY(EditAnywhere)
		int maxSpeedOfPawnNormal;
};
