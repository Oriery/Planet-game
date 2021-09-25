// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Main.h"

// Sets default values
APawn_Main::APawn_Main()
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

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	VisibleMeshBody->SetSimulatePhysics(true);
	VisibleMeshBody->SetEnableGravity(false);
	VisibleMeshHead->SetSimulatePhysics(true);
	VisibleMeshHead->SetEnableGravity(false);
	VisibleMeshBody->SetLinearDamping(1);
	VisibleMeshBody->SetAngularDamping(1);

}

// Called when the game starts or when spawned
void APawn_Main::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawn_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawn_Main::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	//InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveForward", this, &APawn_Main::MoveForwardAxis);
	InputComponent->BindAxis("MoveRight", this, &APawn_Main::MoveRightAxis);
	InputComponent->BindAxis("RotateX", this, &APawn_Main::RotateXAxis);
	InputComponent->BindAxis("RotateY", this, &APawn_Main::RotateYAxis);
}

void APawn_Main::MoveRightAxis(float AxisValue)
{
	VisibleMeshBody->SetPhysicsLinearVelocity(AxisValue * GetActorRightVector(), true);
}

void APawn_Main::MoveForwardAxis(float AxisValue)
{
	VisibleMeshBody->SetPhysicsLinearVelocity(GetActorForwardVector() * AxisValue, true);
}

void APawn_Main::RotateXAxis(float AxisValue)
{
	AddActorLocalRotation(FRotator(0, AxisValue, 0));
}

void APawn_Main::RotateYAxis(float AxisValue)
{
	VisibleMeshHead->AddLocalRotation(FRotator(AxisValue, 0, 0));
}
