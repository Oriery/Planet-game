// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);
 
#include "PawnWithPlanetHorizon.h"
#include "Net/UnrealNetwork.h"
#include "MainActionInterface.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APawnWithPlanetHorizon::APawnWithPlanetHorizon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshMass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshMass"));

	VisibleMeshBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBody"));
	VisibleMeshBody->SetupAttachment(MeshMass);
	VisibleMeshBody->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	VisibleMeshHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHead"));
	VisibleMeshHead->SetupAttachment(VisibleMeshBody);
	VisibleMeshHead->SetRelativeLocation(FVector(0.0f, 0.0f, -20.0f));

	CameraFPS = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFPS"));
	CameraFPS->SetupAttachment(VisibleMeshHead);
	CameraFPS->SetRelativeLocation(FVector(15.0f, 0.0f, 20.0f));
	CameraFPS->SetRelativeRotation(FRotator(-20, 0, 0));

	AutoPossessPlayer = EAutoReceiveInput::Disabled;

	MeshMass->SetVisibility(false);
	MeshMass->SetSimulatePhysics(true);
	MeshMass->SetEnableGravity(false);
	VisibleMeshBody->SetSimulatePhysics(false);
	VisibleMeshBody->SetEnableGravity(false);
	VisibleMeshHead->SetSimulatePhysics(false);
	VisibleMeshHead->SetEnableGravity(false);

	MeshMass->SetLinearDamping(0);
	MeshMass->SetAngularDamping(5);

	SetRootComponent(MeshMass);

	NetUpdateFrequency = 40;
	MinNetUpdateFrequency = 2;

	CameraVerticalAngleMin = -60;
	CameraVerticalAngleMax = 60;

	bReplicates = true;
	SetReplicateMovement(true);

	isHoldingSmth = false;
	team = ETeams::TEAM_A;
}

// Called when the game starts or when spawned
void APawnWithPlanetHorizon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithPlanetHorizon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector posToPlanet = GetActorLocation() - LocationOfCenterOfGravity;
		posToPlanet.Normalize();
		FRotator rot = UKismetMathLibrary::MakeRotFromZX(posToPlanet, GetActorForwardVector());
		SetActorRotation(rot);
		SetActorLocation((posToPlanet * RadiusOfPlanet) + LocationOfCenterOfGravity);

		VisibleMeshBody->SetPhysicsAngularVelocityInDegrees(FVector(0., 0., 0.));
		VisibleMeshHead->SetPhysicsAngularVelocityInDegrees(FVector(0., 0., 0.));

		VisibleMeshBody->SetPhysicsLinearVelocity(FVector::VectorPlaneProject(VisibleMeshBody->GetPhysicsLinearVelocity(), posToPlanet).GetClampedToMaxSize(maxSpeedOfPawn));
	}
	else if (!IsLocallyControlled())
	{
		VisibleMeshHead->SetRelativeRotation(FRotator(WantedByServerRotOfCharacter.Pitch, 0, 0));
		VisibleMeshHead->SetPhysicsAngularVelocityInDegrees(FVector(0., 0., 0.));
		VisibleMeshBody->SetRelativeRotation(FRotator(0, WantedByServerRotOfCharacter.Yaw, 0));
		VisibleMeshBody->SetPhysicsAngularVelocityInDegrees(FVector(0., 0., 0.));
	}
}

void APawnWithPlanetHorizon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("MouseLeftClick", IE_Pressed, this, &APawnWithPlanetHorizon::MouseLeftClick);
	//InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveForward", this, &APawnWithPlanetHorizon::MoveForwardAxis);
	InputComponent->BindAxis("MoveRight", this, &APawnWithPlanetHorizon::MoveRightAxis);
	InputComponent->BindAxis("RotateX", this, &APawnWithPlanetHorizon::RotateXAxis);
	InputComponent->BindAxis("RotateY", this, &APawnWithPlanetHorizon::RotateYAxis);
}

void APawnWithPlanetHorizon::MouseLeftClick()
{
	FVector posStart = CameraFPS->GetComponentLocation();
	FVector posFinish = posStart + CameraFPS->GetForwardVector() * 100;
	ServerRPC_TraceAndClickActor(posStart, posFinish);
}

void APawnWithPlanetHorizon::MoveRightAxis(float AxisValue)
{
	ServerRPC_MoveRightAxis(AxisValue);
}

void APawnWithPlanetHorizon::MoveForwardAxis(float AxisValue)
{
	ServerRPC_MoveForwardAxis(AxisValue);
}

void APawnWithPlanetHorizon::RotateXAxis(float AxisValue)
{
	//VisibleMeshBody->AddLocalRotation(FRotator(0, AxisValue, 0));
	ServerRPC_RotateXAxis(VisibleMeshBody->GetRelativeRotation().Yaw);

	FRotator rot = VisibleMeshBody->GetRelativeRotation() + FRotator(0, AxisValue, 0);

	VisibleMeshBody->SetRelativeRotation(rot);
	ServerRPC_RotateYAxis(rot.Yaw);
}

void APawnWithPlanetHorizon::RotateYAxis(float AxisValue)
{
	FRotator rot = VisibleMeshHead->GetRelativeRotation() + FRotator(AxisValue, 0, 0);

	if (rot.Pitch > CameraVerticalAngleMax)
	{
		rot.Pitch = CameraVerticalAngleMax;
	}
	else if (rot.Pitch < CameraVerticalAngleMin)
	{
		rot.Pitch = CameraVerticalAngleMin;
	}
	VisibleMeshHead->SetRelativeRotation(rot);
	ServerRPC_RotateYAxis(rot.Pitch);
}

void APawnWithPlanetHorizon::ServerRPC_TraceAndClickActor_Implementation(FVector posStart, FVector posFinish)
{
	if (isHoldingSmth)
	{
		IMainActionInterface* holdedActor = Cast<IMainActionInterface>(whatActorHolding);
		holdedActor->mouseLeftClick(this, nullptr);
	}
	else
	{
		FHitResult hitResult;
		FCollisionQueryParams collisionParams;
		TArray<UPrimitiveComponent*> componentsToIgnore;
		collisionParams.AddIgnoredActor(this);
		collisionParams.bTraceComplex = false;


		bool smthIsHit = GetWorld()->LineTraceSingleByChannel(hitResult, posStart, posFinish, ECC_Visibility, collisionParams);

		if (smthIsHit)
		{
			//print("Hitted: " + hitResult.Actor->GetName() + " ::: " + hitResult.Component->GetName());
			//DrawDebugLine(GetWorld(), posStart, posFinish, FColor::Green, false, 5.f, 0, 1);
			IMainActionInterface* hittedActor = Cast<IMainActionInterface>(hitResult.Actor);
			if (hittedActor)
			{
				hittedActor->mouseLeftClick(this, hitResult.Component.Get());
			}
		}
	}
}

void APawnWithPlanetHorizon::ServerRPC_MoveRightAxis_Implementation(float AxisValue)
{
	if (AxisValue)
	{
		FVector	spdToAddTemp = VisibleMeshBody->GetRightVector() * AxisValue;
		float coof = 1;
		if (FVector::DotProduct(MeshMass->GetPhysicsLinearVelocity(), spdToAddTemp) < -3)
		{
			coof = 3;
		}
		
		MeshMass->SetPhysicsLinearVelocity(spdToAddTemp * 3 * coof, true);
	}
	else
	{
		FVector rightSpd = MeshMass->GetPhysicsLinearVelocity().ProjectOnToNormal(VisibleMeshBody->GetRightVector());
		MeshMass->SetPhysicsLinearVelocity(-rightSpd.GetClampedToMaxSize(2), true);
	}
}

void APawnWithPlanetHorizon::ServerRPC_MoveForwardAxis_Implementation(float AxisValue)
{
	if (AxisValue)
	{
		FVector	spdToAddTemp = VisibleMeshBody->GetForwardVector() * AxisValue;
		float coof = 1;
		if (FVector::DotProduct(MeshMass->GetPhysicsLinearVelocity(), spdToAddTemp) < -3)
		{
			coof = 3;
		}
		MeshMass->SetPhysicsLinearVelocity(spdToAddTemp * 3 * coof, true);
	}
	else
	{
		FVector fwdSpd = MeshMass->GetPhysicsLinearVelocity().ProjectOnToNormal(VisibleMeshBody->GetForwardVector());
		MeshMass->SetPhysicsLinearVelocity(- fwdSpd.GetClampedToMaxSize(2), true);
	}
}

void APawnWithPlanetHorizon::ServerRPC_RotateXAxis_Implementation(float WantedAngleCameraX)
{
	VisibleMeshBody->SetRelativeRotation(FRotator(0, WantedAngleCameraX, 0));
	WantedByServerRotOfCharacter.Yaw = WantedAngleCameraX;
}

void APawnWithPlanetHorizon::ServerRPC_RotateYAxis_Implementation(float WantedAngleCameraY)
{
	VisibleMeshHead->SetRelativeRotation(FRotator(WantedAngleCameraY, 0, 0));
	WantedByServerRotOfCharacter.Pitch = WantedAngleCameraY;
}

void APawnWithPlanetHorizon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APawnWithPlanetHorizon, team);
	DOREPLIFETIME(APawnWithPlanetHorizon, WantedByServerRotOfCharacter); 
}
