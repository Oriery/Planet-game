// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorBox.h"

AActorBox::AActorBox() : AActorWithPlanetGravity::AActorWithPlanetGravity()
{
	CostOfBox = 10;
	bIsPacked = false;
}

int AActorBox::GetCost()
{
	return CostOfBox;
}

void AActorBox::SetCost(int newCost)
{
	CostOfBox = newCost;
}

void AActorBox::AddCost(int addCost)
{
	CostOfBox += addCost;
}

void AActorBox::SetIsPacked(bool isPacked)
{
	bIsPacked = isPacked;
}

bool AActorBox::GetIsPacked()
{
	return bIsPacked;
}
