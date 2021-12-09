// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveStaticActor.h"
#include "InteractiveButton.generated.h"

/**
 * 
 */
UCLASS()
class PLANET_STRAT_API AInteractiveButton : public AInteractiveStaticActor
{
	GENERATED_BODY()
	
public:
	AInteractiveButton();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* PlaceOfButtonDefault;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* PlaceOfButtonWhenPressed;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_reactGraphicallyToPress(bool switchingOn = true);

	virtual void reactGraphicallyToPress(bool switchingOn = true) override;

	void ResetPositionOfButtonToDefault();
};
