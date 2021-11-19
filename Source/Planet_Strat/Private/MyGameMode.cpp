
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, text);

#include "MyGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PawnNormal.h"
#include "ActorPlanet.h"

AMyGameMode::AMyGameMode()
{
	TArray<AActor*> arrOfSpawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStartForPlanet::StaticClass(), arrOfSpawns);

	for (AActor* spawner : arrOfSpawns)
	{	
		APlayerStartForPlanet* spawnerTemp = Cast<APlayerStartForPlanet>(spawner);
		if (spawnerTemp)
		{
			if (!Spawners.Contains(spawnerTemp))
			{
				Spawners.Add(spawnerTemp);
			}
		}
	}
}


void AMyGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	print("Handle starting new player");
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

	if (!ActorOfCenterOfGravity)
	{
		TArray<AActor*> arrOfPlanets;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorPlanet::StaticClass(), arrOfPlanets);
		ActorOfCenterOfGravity = arrOfPlanets[0];
	}

	if (ActorOfCenterOfGravity)
	{
		if (spawner)
		{
			FVector locatOfPlanet = ActorOfCenterOfGravity->GetActorLocation();
			FVector vec = spawner->GetActorLocation() - locatOfPlanet;
			vec.Normalize();
			vec = vec * (RadiusOfPlanet + 300);
			FTransform tran = FTransform(spawner->GetActorRotation(), vec + locatOfPlanet, spawner->GetActorScale());
			AActor* spawnedActor = GetWorld()->SpawnActorDeferred<AActor>(DefaultPawnClass, tran);
			APawnWithPlanetHorizon* pawnWithPlanetHorizon = Cast<APawnWithPlanetHorizon>(spawnedActor);
			pawnWithPlanetHorizon->LocationOfCenterOfGravity = locatOfPlanet;
			pawnWithPlanetHorizon->RadiusOfPlanet = RadiusOfPlanet;
			pawnWithPlanetHorizon->maxSpeedOfPawn = maxSpeedOfPawnNormal;
			UGameplayStatics::FinishSpawningActor(spawnedActor, tran);

			NewPlayer->Possess((APawn*)pawnWithPlanetHorizon);
		}
		else
		{
			print("No available spawners for new player to join! Calling Super::HandleStartingNewPlayer");
			Super::HandleStartingNewPlayer(NewPlayer);
		}
	}
	else
	{
		print("Error. Calling Super::HandleStartingNewPlayer");
		Super::HandleStartingNewPlayer(NewPlayer);
	}
}
