// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Teams.h"
#include "PawnWithPlanetHorizon.generated.h"

UCLASS()
class PLANET_STRAT_API APawnWithPlanetHorizon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnWithPlanetHorizon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshMass;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisibleMeshBody;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisibleMeshHead;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraFPS;

	UPROPERTY(EditAnywhere)
		int CameraVerticalAngleMin;

	UPROPERTY(EditAnywhere)
		int CameraVerticalAngleMax;

	UPROPERTY(VisibleAnywhere)
		float MaxSpeed;

	UPROPERTY(Replicated)
		FRotator WantedByServerRotOfCharacter;

	UPROPERTY(Replicated, BlueprintReadOnly)
		ETeams team;

	void MouseLeftClick();

	void MoveRightAxis(float AxisValue);
	void MoveForwardAxis(float AxisValue);
	void RotateXAxis(float AxisValue);
	void RotateYAxis(float AxisValue);

	UFUNCTION(Server, Reliable)
		void ServerRPC_TraceAndClickActor(FVector posStart, FVector posFinish);

	UFUNCTION(Server, Unreliable)
		void ServerRPC_MoveRightAxis(float AxisValue);
	UFUNCTION(Server, Unreliable)
		void ServerRPC_MoveForwardAxis(float AxisValue);
	UFUNCTION(Server, Unreliable)
		void ServerRPC_RotateXAxis(float WantedAngleCameraX);
	UFUNCTION(Server, Unreliable)
		void ServerRPC_RotateYAxis(float WantedAngleCameraY);

	UPROPERTY()
		FVector LocationOfCenterOfGravity;

	UPROPERTY()
		int RadiusOfPlanet;

	UPROPERTY()
		int maxSpeedOfPawn;

	bool isHoldingSmth;

	AActor* whatActorHolding;

};
