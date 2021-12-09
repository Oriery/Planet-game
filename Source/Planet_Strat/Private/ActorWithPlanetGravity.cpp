// Fill out your copyright notice in the Description page of Project Settings.


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, text);

#include "ActorWithPlanetGravity.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PawnNormal.h"
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

	SetReplicates(true);
	SetReplicateMovement(true);

	isGrabbed = false;
	GravityAcceleration = 8;

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
			print("Box has no reference to ActorOfCenterOfGravity. Using 0,0,0 instead");
		}
	}
}

// Called every frame
void AActorWithPlanetGravity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
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
		if (!isGrabbed && !whoClicked->isHoldingSmth)
		{
			isGrabbed = true;
			grabbedByActor = whoClicked;
			whoClicked->isHoldingSmth = true;
			whoClicked->whatActorHolding = this;

			tempCollisionProfileName = VisibleMesh->GetCollisionProfileName();
			MulticastRPC_setPhysicsEnabledOfMesh(false);
			MulticastRPC_setCollisionProfileOfMesh("OverlapAll");
			FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
			
			AttachToComponent(whoClicked->CameraFPS, rules);
		}
		else if (isGrabbed && grabbedByActor == whoClicked && VisibleMesh->GetOverlapInfos().Num() == 0)
		{
			isGrabbed = false;
			whoClicked->isHoldingSmth = false;

			MulticastRPC_setPhysicsEnabledOfMesh(true);
			MulticastRPC_setCollisionProfileOfMesh(tempCollisionProfileName);

			DetachRootComponentFromParent();
		}
	}
}

void AActorWithPlanetGravity::MulticastRPC_setCollisionProfileOfMesh_Implementation(FName name) {
	VisibleMesh->SetCollisionProfileName(name);
}

void AActorWithPlanetGravity::MulticastRPC_setPhysicsEnabledOfMesh_Implementation(bool enabled) {
	VisibleMesh->SetSimulatePhysics(enabled);
}
