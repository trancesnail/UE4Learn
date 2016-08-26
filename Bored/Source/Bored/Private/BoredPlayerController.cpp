// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredPlayerController.h"

ABoredPlayerController::ABoredPlayerController(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;
}

void ABoredPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{

}

void ABoredPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

/** set desired camera position. */
void ABoredPlayerController::SetCameraTarget(const FVector& CameraTarget)
{
	//if (GetCameraComponent() != NULL)
	//{
	//	GetCameraComponent()->SetCameraTarget(CameraTarget);
	//}
}

/** Handler for mouse leaving the minimap. */
void ABoredPlayerController::MouseLeftMinimap()
{
	//if (GetCameraComponent() != NULL)
	//{
	//	GetCameraComponent()->EndSwipeNow();
	//}
}

/** Handler for mouse pressed over minimap. */
void ABoredPlayerController::MousePressedOverMinimap()
{
	//if (GetCameraComponent() != NULL)
	//{
	//	GetCameraComponent()->EndSwipeNow();
	//}
}

/** Handler for mouse release over minimap. */
void ABoredPlayerController::MouseReleasedOverMinimap()
{
	//if (GetCameraComponent() != NULL)
	//{
	//	GetCameraComponent()->EndSwipeNow();
	//}
}