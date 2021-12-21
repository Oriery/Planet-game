// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "BoxReceiver.h"
#include "PawnNormal.h"
#include "Conveyor.h"

// Sets default values
ABoxReceiver::ABoxReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(VisibleMesh);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABoxReceiver::OnOverlapBegin);

	team = ETeams::TEAM_A;
}

// Called when the game starts or when spawned
void ABoxReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxReceiver::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (AActorBox* box = Cast<AActorBox>(OtherActor))
		{
			if (box->isGrabbed)
			{
				if (APawnNormal* pawnNormal = Cast<APawnNormal>(box->grabbedByActor))
				{
					pawnNormal->isHoldingSmth = false;
					box->detachFromPawn();
				}
				else if (AConveyor* conveyor = Cast<AConveyor>(box->grabbedByActor))
				{
					conveyor->boxesToMove.Remove(box);
				}
				else
				{
					print("BoxReceiver wanted to receive box, but it is now grabbed by unknown class");
				}
			}

			OnBoxReceive(box);
		}
	}
}

