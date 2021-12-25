// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameSession.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

void AMyGameSession::RegisterServer()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();

	FOnlineSessionSettings Settings;
	Settings.bIsDedicated = true;
	Settings.bIsLANMatch = true;
	Settings.bAllowJoinInProgress = true;
	Settings.bShouldAdvertise = true;
	Settings.NumPublicConnections = 12;
	Settings.bUsesPresence = true;
	Session->CreateSession(0, GameSessionName, Settings);
	UE_LOG(LogTemp, Log, TEXT("SessionCreated   --------------------------------"));
}
