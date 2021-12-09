// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainActionInterface.h"
#include "InteractiveStaticActor.generated.h"

UCLASS()
class PLANET_STRAT_API AInteractiveStaticActor : public AActor, public IMainActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveStaticActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisibleMeshStaticPart;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisibleMeshMovingPart;

	virtual void mouseLeftClick(APawn* PawnWhoClicked, UPrimitiveComponent* hitComponent) override;

	UPROPERTY(EditAnywhere)
	AActor* ActorToCallMainAction;

	bool isOn;

	UPROPERTY(EditAnywhere)
		bool isToogle;

	void SendMainActionSignal();

	virtual void reactGraphicallyToPress(bool switchingOn = true) {};
};
