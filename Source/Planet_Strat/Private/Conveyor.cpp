// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "Conveyor.h"
#include "PawnNormal.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AConveyor::AConveyor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(VisibleMesh);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AConveyor::OnOverlapBegin);

	TargetDestination = CreateDefaultSubobject<USceneComponent>(TEXT("TargetDestination"));
	TargetDestination->SetupAttachment(TriggerBox);

	CentreOfEffects = CreateDefaultSubobject<USceneComponent>(TEXT("CentreOfEffects"));
	CentreOfEffects->SetupAttachment(VisibleMesh);

	speedOfBoxes = 40;
	orderOfConveyor = 0;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AConveyor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConveyor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (boxesToMove.Num() > 0)
		{
			AActorWithPlanetGravity* box;
			FVector vec;
			for (int i = 0; i < boxesToMove.Num(); i++)
			{
				box = boxesToMove[i];
				vec = TargetDestination->GetComponentLocation() - box->GetActorLocation();
				vec.Normalize();
				vec = (box->VisibleMesh->GetPhysicsLinearVelocity() + vec * speedOfBoxes * 2).GetClampedToMaxSize(speedOfBoxes);
				box->VisibleMesh->SetPhysicsLinearVelocity(vec);
			}
		}
	}
	else
	{	
		if (boxesToMove.Num() > 0)
		{	
			UStaticMeshComponent* meshOfEffect;
			while (MeshesOfEffectsStatic.Num() < boxesToMove.Num()) // add if not enough
			{
				meshOfEffect = NewObject<UStaticMeshComponent>(this);

				meshOfEffect->RegisterComponent();
				meshOfEffect->SetStaticMesh(MeshForEffect);
				meshOfEffect->AttachToComponent(CentreOfEffects, FAttachmentTransformRules::KeepRelativeTransform);
				meshOfEffect->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				
				if (MeshesOfEffectsMoving.Num() == MeshesOfEffectsStatic.Num())
				{
					MeshesOfEffectsMoving.Add(meshOfEffect);
				}
				else
				{
					MeshesOfEffectsStatic.Add(meshOfEffect);
				}
			}
			while (MeshesOfEffectsStatic.Num() > boxesToMove.Num()) // destroy if too many
			{
				MeshesOfEffectsStatic.Pop()->DestroyComponent();
				MeshesOfEffectsMoving.Pop()->DestroyComponent();
			}

			FVector vec;
			for (int i = 0; i < boxesToMove.Num(); i++)
			{
				vec = boxesToMove[i]->GetActorLocation() - CentreOfEffects->GetComponentLocation();

				FRotator rot = UKismetMathLibrary::MakeRotFromX(vec);
				MeshesOfEffectsStatic[i]->SetWorldRotation(rot);

				rot = UKismetMathLibrary::MakeRotFromX(-vec);
				MeshesOfEffectsMoving[i]->SetWorldRotation(rot);
				MeshesOfEffectsMoving[i]->SetWorldLocation(CentreOfEffects->GetComponentLocation() + vec.GetClampedToSize(63, 1000));
			}
		}
		else
		{
			while (MeshesOfEffectsStatic.Num() > 0) // destroy if too many
			{
				MeshesOfEffectsStatic.Pop()->DestroyComponent();
				MeshesOfEffectsMoving.Pop()->DestroyComponent();
			}
		}
	}
}

void AConveyor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{		
		if (AActorBox* box = Cast<AActorBox>(OtherActor))
		{
			bool takeBox = box->GetCanBeGrabbedByConveyor();

			if (takeBox && box->isGrabbed)
			{
				if (APawnNormal* pawnNormal = Cast<APawnNormal>(box->grabbedByActor))
				{
					pawnNormal->isHoldingSmth = false;
					box->detachFromPawn();
				}
				else if (AConveyor* conveyor = Cast<AConveyor>(box->grabbedByActor))
				{
					if (conveyor->orderOfConveyor < orderOfConveyor)
					{
						conveyor->boxesToMove.Remove(box);
					}
					else
					{
						takeBox = false;
					}
				}
				else
				{
					print("Conveyor wanted to grab box, but it is now grabbed by unknown class");
				}
			}
			if (takeBox)
			{
				box->shouldApplyGravity = false;
				box->isGrabbed = true;
				box->grabbedByActor = this;
				boxesToMove.Add(box);
			}
		}
	}
}

void AConveyor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AConveyor, boxesToMove);
}
