// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ActorBox.h"
#include "Teams.h"
#include "BoxReceiver.generated.h"

UCLASS()
class PLANET_STRAT_API ABoxReceiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxReceiver();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisibleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnBoxReceive(AActorBox* box) {};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	ETeams team;

};
