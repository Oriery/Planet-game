// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxReceiver.h"
#include "BoxSender.generated.h"

/**
 * 
 */
UCLASS()
class PLANET_STRAT_API ABoxSender : public ABoxReceiver
{
	GENERATED_BODY()
	
protected:

	virtual void OnBoxReceive(AActorBox* box) override;
};
