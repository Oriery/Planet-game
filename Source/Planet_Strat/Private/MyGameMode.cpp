
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "MyGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PawnNormal.h"
#include "MyPlayerState.h"
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
			Spawners.Add(spawnerTemp);
		}
	}

	bLastAddedPlayerIsTeamA = false;
}


void AMyGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	print("Handle starting new player");

	AMyPlayerState* playerState = NewPlayer->GetPlayerState<AMyPlayerState>();

	if (playerState)
	{
		playerState->team = decideWhichTeamIsNewPlayer();
	}
	else
	{
		print("Player State is not of a wanted class");
		return;
	}

	APlayerStartForPlanet* spawner = nullptr;
	for (APlayerStartForPlanet* spawnerTemp : Spawners)
	{
		if (playerState->team == spawnerTemp->team && spawnerTemp->TriggerBox->GetOverlapInfos().Num() == 0)
		{
			spawner = spawnerTemp;
			break;
		}
	}

	if (!spawner)
	{
		print("No available spawners for new player to join!");
		return;
	}

	if (!ActorOfCenterOfGravity)
	{
		TArray<AActor*> arrOfPlanets;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActorPlanet::StaticClass(), arrOfPlanets);
		if (arrOfPlanets.Num() < 1)
		{
			print("No Planet Found.");
			return;
		}
		ActorOfCenterOfGravity = arrOfPlanets[0];
	}
	
	FVector locatOfPlanet = ActorOfCenterOfGravity->GetActorLocation();
	FVector vec = spawner->GetActorLocation() - locatOfPlanet;
	vec.Normalize();
	vec = vec * (RadiusOfPlanet);
	FTransform tran = FTransform(spawner->GetActorRotation(), vec + locatOfPlanet, spawner->GetActorScale());
	AActor* spawnedActor = GetWorld()->SpawnActorDeferred<AActor>(DefaultPawnClass, tran);
	APawnWithPlanetHorizon* pawnWithPlanetHorizon = Cast<APawnWithPlanetHorizon>(spawnedActor);
	pawnWithPlanetHorizon->LocationOfCenterOfGravity = locatOfPlanet;
	pawnWithPlanetHorizon->RadiusOfPlanet = RadiusOfPlanet;
	pawnWithPlanetHorizon->maxSpeedOfPawn = maxSpeedOfPawnNormal;
	pawnWithPlanetHorizon->team = playerState->team;
	UGameplayStatics::FinishSpawningActor(spawnedActor, tran);

	NewPlayer->Possess((APawn*)pawnWithPlanetHorizon);
}

ETeams AMyGameMode::decideWhichTeamIsNewPlayer()
{
	bLastAddedPlayerIsTeamA = !bLastAddedPlayerIsTeamA;
	if (bLastAddedPlayerIsTeamA)
	{
		return ETeams::TEAM_A;
	}
	else
	{
		return ETeams::TEAM_B;
	}
}
