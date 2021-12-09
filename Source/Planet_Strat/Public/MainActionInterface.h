// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMainActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLANET_STRAT_API IMainActionInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void mainAction() {};
	virtual void mouseLeftClick(APawn* PawnWhoClicked, UPrimitiveComponent* hitComponent) {};
};
