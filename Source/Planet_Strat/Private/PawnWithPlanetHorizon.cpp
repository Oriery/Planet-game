// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithPlanetHorizon.h"

// Sets default values
APawnWithPlanetHorizon::APawnWithPlanetHorizon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMeshBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBody"));
	VisibleMeshBody->SetupAttachment(RootComponent);

	VisibleMeshHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHead"));
	VisibleMeshHead->SetupAttachment(VisibleMeshBody);
	VisibleMeshHead->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));

	CameraFPS = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFPS"));
	CameraFPS->SetupAttachment(VisibleMeshHead);
	CameraFPS->SetRelativeLocation(FVector(15.0f, 0.0f, 20.0f));
	CameraFPS->SetRelativeRotation(FRotator(-20, 0, 0));

	AutoPossessPlayer = EAutoReceiveInput::Disabled;

	VisibleMeshBody->SetSimulatePhysics(true);
	VisibleMeshBody->SetEnableGravity(false);
	VisibleMeshHead->SetSimulatePhysics(true);
	VisibleMeshHead->SetEnableGravity(false);
	VisibleMeshBody->SetLinearDamping(0);
	VisibleMeshBody->SetAngularDamping(5);

	VisibleMeshHead->SetIsReplicated(true);

	NetUpdateFrequency = 40;
	MinNetUpdateFrequency = 2;

	//VisibleMeshBody->SetPhysicsLinearVelocity(100 * GetActorRightVector(), true);
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

}

// Called to bind functionality to input
void APawnWithPlanetHorizon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	//InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveForward", this, &APawnWithPlanetHorizon::MoveForwardAxis);
	InputComponent->BindAxis("MoveRight", this, &APawnWithPlanetHorizon::MoveRightAxis);
	InputComponent->BindAxis("RotateX", this, &APawnWithPlanetHorizon::RotateXAxis);
	InputComponent->BindAxis("RotateY", this, &APawnWithPlanetHorizon::RotateYAxis);
}



void APawnWithPlanetHorizon::MoveRightAxis(float AxisValue)
{
	ServerRPC_MoveRightAxis(AxisValue);
	//VisibleMeshBody->SetPhysicsLinearVelocity(AxisValue * GetActorRightVector(), true);
}

void APawnWithPlanetHorizon::MoveForwardAxis(float AxisValue)
{
	ServerRPC_MoveForwardAxis(AxisValue);
	//VisibleMeshBody->SetPhysicsLinearVelocity(GetActorForwardVector() * AxisValue, true);
}

void APawnWithPlanetHorizon::RotateXAxis(float AxisValue)
{
	ServerRPC_RotateXAxis(AxisValue);
	//AddActorLocalRotation(FRotator(0, AxisValue, 0));
}

void APawnWithPlanetHorizon::RotateYAxis(float AxisValue)
{
	ServerRPC_RotateYAxis(AxisValue);
	//VisibleMeshHead->AddLocalRotation(FRotator(AxisValue, 0, 0));
}


void APawnWithPlanetHorizon::ServerRPC_MoveRightAxis_Implementation(float AxisValue)
{
	VisibleMeshBody->SetPhysicsLinearVelocity(AxisValue * GetActorRightVector(), true);
}

void APawnWithPlanetHorizon::ServerRPC_MoveForwardAxis_Implementation(float AxisValue)
{
	VisibleMeshBody->SetPhysicsLinearVelocity(GetActorForwardVector() * AxisValue, true);
}

void APawnWithPlanetHorizon::ServerRPC_RotateXAxis_Implementation(float AxisValue)
{
	AddActorLocalRotation(FRotator(0, AxisValue, 0));
}

void APawnWithPlanetHorizon::ServerRPC_RotateYAxis_Implementation(float AxisValue)
{
	VisibleMeshHead->AddLocalRotation(FRotator(AxisValue, 0, 0));
}
