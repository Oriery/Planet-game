// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Teams.h"
#include "BillboardWithInfo.generated.h"

UCLASS()
class PLANET_STRAT_API ABillboardWithInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABillboardWithInfo();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisibleMesh;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderScoreOfTeamA;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderScoreOfTeamB;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetScoreForTeam(ETeams team, int scoreToShow);

};
