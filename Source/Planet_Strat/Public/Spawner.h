// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainActionInterface.h"
#include "Components/TextRenderComponent.h"
#include "Spawner.generated.h"

UCLASS()
class PLANET_STRAT_API ASpawner : public AActor, public IMainActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRender;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int CooldownLength;

	void EndOfCooldown();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void mainAction() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WhatToSpawn;

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRPC_SetVisibilityOfTextRender(bool bVisible);

	bool bIsNotOnCooldown;
};
