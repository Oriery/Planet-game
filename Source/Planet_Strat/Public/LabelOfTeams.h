// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabelOfTeams.generated.h"

UCLASS()
class PLANET_STRAT_API ALabelOfTeams : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabelOfTeams();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisibleMesh;

	FVector OriginalLocation;

	UPROPERTY(EditDefaultsOnly)
		float DeltaHeight;

	UPROPERTY(EditDefaultsOnly)
		float HeightFrequency;

	UPROPERTY(EditDefaultsOnly)
		float RotationSpeed;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
