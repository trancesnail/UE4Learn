// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredGameMode.h"


ABoredGameMode::ABoredGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = ABoredPlayerController::StaticClass();
	GameStateClass = ABoredGameState::StaticClass();
	HUDClass = ABoredHUD::StaticClass();
	if ((GEngine != nullptr) && (GEngine->GameViewport != nullptr))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}

