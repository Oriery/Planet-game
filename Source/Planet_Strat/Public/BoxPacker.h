// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxReceiver.h"
#include "BoxPacker.generated.h"

/**
 * 
 */
UCLASS()
class PLANET_STRAT_API ABoxPacker : public ABoxReceiver
{
	GENERATED_BODY()

public:
	ABoxPacker();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* TargetDestination;
	
protected:

	virtual void OnBoxReceive(AActorBox* box) override;
};
