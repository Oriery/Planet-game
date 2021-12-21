// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSender.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameState.h"

void ABoxSender::OnBoxReceive(AActorBox* box)
{
	if (box->GetIsPacked())
	{
		if (AMyGameState* gs = Cast<AMyGameState>(UGameplayStatics::GetGameState(GetWorld())))
		{
			gs->AddScoreForTeam(team, box->GetCost());
		}

		box->Destroy();
	}
}