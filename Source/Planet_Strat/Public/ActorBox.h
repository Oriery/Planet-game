// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithPlanetGravity.h"
#include "ActorBox.generated.h"

/**
 * 
 */
UCLASS()
class PLANET_STRAT_API AActorBox : public AActorWithPlanetGravity
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	int CostOfBox;

	bool bIsPacked;

public:
	AActorBox();

	int GetCost();
	void SetCost(int newCost);
	void AddCost(int addCost);

	void SetIsPacked(bool isPacked);
	bool GetIsPacked();
};
