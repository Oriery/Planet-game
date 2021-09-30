// Copyright Epic Games, Inc. All Rights Reserved.


#include "Planet_StratGameModeBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PawnNormal.h"

APlanet_StratGameModeBase::APlanet_StratGameModeBase()
{

	TArray<AActor*> arrOfSpawns; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStartForPlanet::StaticClass(), arrOfSpawns);

	for (AActor* spawner : arrOfSpawns)
	{
		if (APlayerStartForPlanet * spawnerTemp = Cast<APlayerStartForPlanet>(spawner))
		{
			Spawners.Add(spawnerTemp);
		}
	}
}


void APlanet_StratGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	APlayerStartForPlanet* spawner = nullptr;
	for (APlayerStartForPlanet* spawnerTemp : Spawners)
	{
		if (spawnerTemp->isFree)
		{
			spawnerTemp->isFree = false;
			spawner = spawnerTemp;
			break;
		}
	}
	
	if (spawner != nullptr)
	{
		FActorSpawnParameters params;
		params.bNoFail = true;
		params.Owner = NewPlayer;
		FTransform tran;
		tran = spawner->SpawnPoint->GetComponentTransform();
		AActor* spawnedActor = GetWorld()->SpawnActor(DefaultPawnClass, &tran, params);
		NewPlayer->Possess((APawn*)spawnedActor);
	} 
}
