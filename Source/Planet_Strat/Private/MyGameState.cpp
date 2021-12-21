// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "MyGameState.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyGameState::AMyGameState() : AGameState::AGameState()
{
	scoreOfTeamsInThisRound.Init(0, 4);
}

void AMyGameState::OnRep_scoreOfTeamsInThisRound()
{
	if (BillboardsWithInfo.Num() < 1)
	{
		TArray<AActor*> arrOfActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABillboardWithInfo::StaticClass(), arrOfActors);
		if (arrOfActors.Num() < 1)
		{
			print("No Billboars Found.");
			return;
		}
		for (AActor* actor : arrOfActors)
		{
			BillboardsWithInfo.Add(Cast<ABillboardWithInfo>(actor));
		}
	}

	for (ABillboardWithInfo* Billboard : BillboardsWithInfo)
	{
		Billboard->SetScoreForTeam(ETeams::TEAM_A, GetScoreOfTeam(ETeams::TEAM_A));
		Billboard->SetScoreForTeam(ETeams::TEAM_B, GetScoreOfTeam(ETeams::TEAM_B));
		//Billboard->SetScoreForTeam(ETeams::TEAM_C, GetScoreOfTeam(ETeams::TEAM_C));
		//Billboard->SetScoreForTeam(ETeams::TEAM_D, GetScoreOfTeam(ETeams::TEAM_D));
	}
}

void AMyGameState::AddScoreForTeam(ETeams team, int scoreToAdd)
{
	int i = 0;
	switch (team)
	{
	case ETeams::TEAM_A:
		i = 0;
		break;
	case ETeams::TEAM_B:
		i = 1;
		break;
	case ETeams::TEAM_C:
		i = 2;
		break;
	case ETeams::TEAM_D:
		i = 3;
		break;
	}

	scoreOfTeamsInThisRound[i] += scoreToAdd;
}

int AMyGameState::GetScoreOfTeam(ETeams team)
{
	int i = 0;
	switch (team)
	{
	case ETeams::TEAM_A:
		i = 0;
		break;
	case ETeams::TEAM_B:
		i = 1;
		break;
	case ETeams::TEAM_C:
		i = 2;
		break;
	case ETeams::TEAM_D:
		i = 3;
		break;
	}

	return scoreOfTeamsInThisRound[i];
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyGameState, scoreOfTeamsInThisRound);
}
