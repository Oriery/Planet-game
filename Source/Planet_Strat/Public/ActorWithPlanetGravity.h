// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainActionInterface.h"
#include "ActorWithPlanetGravity.generated.h"

UCLASS()
class PLANET_STRAT_API AActorWithPlanetGravity : public AActor, public IMainActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorWithPlanetGravity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void mouseLeftClick(APawn* PawnWhoClicked, UPrimitiveComponent* hitComponent) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisibleMesh;

	UPROPERTY(EditAnywhere)
	AActor* ActorOfCenterOfGravity;

	FVector LocationOfCenterOfGravity;

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRPC_setCollisionProfileOfMesh(FName name);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRPC_setPhysicsEnabledOfMesh(bool enabled);

	bool isGrabbed;

	FName tempCollisionProfileName;

	AActor* grabbedByActor;

	UPROPERTY(EditAnywhere)
	float GravityAcceleration;
};
