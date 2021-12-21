// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Teams.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETeams : uint8
{
	TEAM_A UMETA(DisplayName = "A"),
	TEAM_B UMETA(DisplayName = "B"),
	TEAM_C UMETA(DisplayName = "C"),
	TEAM_D UMETA(DisplayName = "D")
};
