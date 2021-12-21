// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxPacker.h"

ABoxPacker::ABoxPacker() : ABoxReceiver::ABoxReceiver()
{
	TargetDestination = CreateDefaultSubobject<USceneComponent>(TEXT("TargetDestination"));
	TargetDestination->SetupAttachment(VisibleMesh);
}

void ABoxPacker::OnBoxReceive(AActorBox* box)
{
	box->SetActorLocation(TargetDestination->GetComponentLocation());
	box->SetIsPacked(true);
}