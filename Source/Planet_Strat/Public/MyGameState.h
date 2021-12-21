// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Teams.h"
#include "BillboardWithInfo.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class PLANET_STRAT_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMyGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_scoreOfTeamsInThisRound)
	TArray<int> scoreOfTeamsInThisRound;

	UFUNCTION()
	void OnRep_scoreOfTeamsInThisRound();

	TArray<ABillboardWithInfo*> BillboardsWithInfo;

public:
	void AddScoreForTeam(ETeams team, int scoreToAdd);

	UFUNCTION(BlueprintCallable)
	int GetScoreOfTeam(ETeams team);
};
