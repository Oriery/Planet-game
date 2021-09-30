// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerStartForPlanet.h"
#include "Planet_StratGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANET_STRAT_API APlanet_StratGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	APlanet_StratGameModeBase();

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);

	UPROPERTY()
	TArray<APlayerStartForPlanet*> Spawners;
};
