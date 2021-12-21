// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "BillboardWithInfo.h"

// Sets default values
ABillboardWithInfo::ABillboardWithInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));

	TextRenderScoreOfTeamA = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderScoreOfTeamA"));
	TextRenderScoreOfTeamA->SetupAttachment(VisibleMesh);

	TextRenderScoreOfTeamB = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderScoreOfTeamB"));
	TextRenderScoreOfTeamB->SetupAttachment(VisibleMesh);
}

// Called when the game starts or when spawned
void ABillboardWithInfo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABillboardWithInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABillboardWithInfo::SetScoreForTeam(ETeams team, int scoreToShow)
{
	UTextRenderComponent* TextRenderComp = nullptr;
	switch (team)
	{
	case ETeams::TEAM_A:
		TextRenderComp = TextRenderScoreOfTeamA;
		break;
	case ETeams::TEAM_B:
		TextRenderComp = TextRenderScoreOfTeamB;
		break;
	/*case ETeams::TEAM_C:
		i = 2;
		break;
	case ETeams::TEAM_D:
		i = 3;
		break;*/
	default:
		print("Unknown team given to ABillboardWithInfo::SetScoreForTeam");
	}
	if (TextRenderComp)
	{
		TextRenderComp->SetText(FText::FromString(FString::FromInt(scoreToShow)));
	}
}

