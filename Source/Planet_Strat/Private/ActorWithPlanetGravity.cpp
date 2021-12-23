// Fill out your copyright notice in the Description page of Project Settings.


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "ActorWithPlanetGravity.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PawnNormal.h"
#include "Conveyor.h"
#include "MyGameMode.h"

// Sets default values
AActorWithPlanetGravity::AActorWithPlanetGravity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	VisibleMesh->SetSimulatePhysics(true);
	VisibleMesh->SetEnableGravity(false);
	VisibleMesh->SetCollisionProfileName("PhysicsActor");
	VisibleMesh->SetLinearDamping(1);

	SetRootComponent(VisibleMesh);

	bReplicates = true;	
	SetReplicateMovement(true);

	isGrabbed = false;
	GravityAcceleration = 8;
	shouldApplyGravity = true;
	bCanBeGrabbedByConveyor = true;

	if (AMyGameMode* gm = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ActorOfCenterOfGravity = gm->ActorOfCenterOfGravity;
	}
}

// Called when the game starts or when spawned
void AActorWithPlanetGravity::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (ActorOfCenterOfGravity)
		{
			LocationOfCenterOfGravity = ActorOfCenterOfGravity->GetActorLocation();
		}
		else
		{
			LocationOfCenterOfGravity = FVector(0.f, 0.f, 0.f);
			print("AActorWithPlanetGravity has no reference to ActorOfCenterOfGravity. Using 0,0,0 instead");
		}
	}
}

// Called every frame
void AActorWithPlanetGravity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && shouldApplyGravity)
	{
		FVector vec = (GetActorLocation() - LocationOfCenterOfGravity);
		vec.Normalize();
		VisibleMesh->SetPhysicsLinearVelocity(- vec * GravityAcceleration, true);
	}
}

void AActorWithPlanetGravity::mouseLeftClick(APawn* PawnWhoClicked, UPrimitiveComponent* hitComponent)
{
	if (APawnNormal* whoClicked = Cast<APawnNormal>(PawnWhoClicked))
	{
		AConveyor* conv = Cast<AConveyor>(grabbedByActor);
		bool bIsGrabbedByConveyor = isGrabbed && conv != nullptr;

		if ((!isGrabbed || bIsGrabbedByConveyor) && !whoClicked->isHoldingSmth) // then grab box
		{
			if (conv)
			{
				conv->boxesToMove.Remove(this);
				SetCanBeGrabbedByConveyor(false);
				FTimerHandle timerHandle;
				GetWorldTimerManager().SetTimer(timerHandle, this, &AActorWithPlanetGravity::SetCanBeGrabbedByConveyorTrue, 1.0, false, 1);
			}

			isGrabbed = true;
			grabbedByActor = whoClicked;
			whoClicked->isHoldingSmth = true;
			whoClicked->whatActorHolding = this;

			tempCollisionProfileName = VisibleMesh->GetCollisionProfileName();
			MulticastRPC_setPhysicsEnabledOfMesh(false);
			MulticastRPC_setCollisionProfileOfMesh("OverlapAll");
			FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
			SetActorLocation(whoClicked->CameraFPS->GetComponentLocation() + whoClicked->CameraFPS->GetForwardVector() * 60);
			AttachToComponent(whoClicked->CameraFPS, rules);
		}
		else if (isGrabbed && grabbedByActor == whoClicked && VisibleMesh->GetOverlapInfos().Num() == 0) // then release box
		{
			isGrabbed = false;
			whoClicked->isHoldingSmth = false;

			detachFromPawn();

			VisibleMesh->SetPhysicsLinearVelocity(VisibleMesh->GetPhysicsLinearVelocity().GetClampedToMaxSize(whoClicked->maxSpeedOfPawn));
		}
	}
}

void AActorWithPlanetGravity::detachFromPawn()
{
	MulticastRPC_setPhysicsEnabledOfMesh(true);
	MulticastRPC_setCollisionProfileOfMesh(tempCollisionProfileName);

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AActorWithPlanetGravity::detachFromConveyor()
{
	MulticastRPC_setPhysicsEnabledOfMesh(true);
	MulticastRPC_setCollisionProfileOfMesh(tempCollisionProfileName);
}

void AActorWithPlanetGravity::SetCanBeGrabbedByConveyor(bool can)
{
	bCanBeGrabbedByConveyor = can;
}

void AActorWithPlanetGravity::SetCanBeGrabbedByConveyorTrue()
{
	bCanBeGrabbedByConveyor = true;
}

bool AActorWithPlanetGravity::GetCanBeGrabbedByConveyor()
{
	return bCanBeGrabbedByConveyor;
}

void AActorWithPlanetGravity::MulticastRPC_setCollisionProfileOfMesh_Implementation(FName name) 
{
	VisibleMesh->SetCollisionProfileName(name);
}

void AActorWithPlanetGravity::MulticastRPC_setPhysicsEnabledOfMesh_Implementation(bool enabled) 
{
	VisibleMesh->SetSimulatePhysics(enabled);
}
