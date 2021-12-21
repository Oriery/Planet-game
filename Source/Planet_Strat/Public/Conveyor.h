// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ActorBox.h"
#include "Conveyor.generated.h"

UCLASS()
class PLANET_STRAT_API AConveyor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConveyor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisibleMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* TargetDestination;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CentreOfEffects;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* MeshForEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<UStaticMeshComponent*> MeshesOfEffectsStatic;
	TArray<UStaticMeshComponent*> MeshesOfEffectsMoving;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float speedOfBoxes;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(Replicated)
	TArray<AActorWithPlanetGravity*> boxesToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int orderOfConveyor;
};
