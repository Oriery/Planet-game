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

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisibleMesh;

	UPROPERTY(EditAnywhere)
		AActor* ActorOfCenterOfGravity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bCanBeGrabbedByConveyor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void mouseLeftClick(APawn* PawnWhoClicked, UPrimitiveComponent* hitComponent) override;

	FVector LocationOfCenterOfGravity;

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRPC_setCollisionProfileOfMesh(FName name);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRPC_setPhysicsEnabledOfMesh(bool enabled);

	void detachFromPawn(); 
	void detachFromConveyor();

	bool isGrabbed;

	FName tempCollisionProfileName;

	AActor* grabbedByActor;

	UPROPERTY(EditAnywhere)
	float GravityAcceleration;

	bool shouldApplyGravity;

	void SetCanBeGrabbedByConveyor(bool can);
	void SetCanBeGrabbedByConveyorTrue();
	bool GetCanBeGrabbedByConveyor();
};
