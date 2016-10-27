// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredPlayerController.h"
#include "BoredSpectatorPawn.h"
#include "BoredCameraComponent.h"
#include "BoredInput.h"

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
	InputHandler = NewObject<UBoredInput>(this);

	BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &ABoredPlayerController::OnTapPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Pressed, &ABoredPlayerController::OnHoldPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Released, &ABoredPlayerController::OnHoldReleased);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Pressed, &ABoredPlayerController::OnSwipeStarted);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Repeat, &ABoredPlayerController::OnSwipeUpdate);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Released, &ABoredPlayerController::OnSwipeReleased);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Pressed, &ABoredPlayerController::OnSwipeTwoPointsStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Repeat, &ABoredPlayerController::OnSwipeTwoPointsUpdate);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Pressed, &ABoredPlayerController::OnPinchStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Repeat, &ABoredPlayerController::OnPinchUpdate);

	FInputActionBinding& ToggleInGameMenuBinding = InputComponent->BindAction("InGameMenu", IE_Pressed, this, &ABoredPlayerController::OnToggleInGameMenu);
	ToggleInGameMenuBinding.bExecuteWhenPaused = true;
}


ABoredSpectatorPawn* ABoredPlayerController::GetBoredSpectatorPawn() const
{
	return Cast<ABoredSpectatorPawn>(GetSpectatorPawn());
}


UBoredCameraComponent* ABoredPlayerController::GetCameraComponent() const
{
	UBoredCameraComponent* CameraComponent = NULL;
	if (GetBoredSpectatorPawn() != NULL)
	{
		CameraComponent = GetBoredSpectatorPawn()->GetBoredCameraComponent();
	}
	return CameraComponent;
}

/** set desired camera position. */
void ABoredPlayerController::SetCameraTarget(const FVector& CameraTarget)
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->SetCameraTarget(CameraTarget);
	}
}

/** Toggles the ingame menu display. */
void ABoredPlayerController::OnToggleInGameMenu()
{
	ABoredHUD* const MyHUD = Cast<ABoredHUD>(GetHUD());
	if (MyHUD)
	{
		MyHUD->TogglePauseMenu();
	}
}

/** Handler for mouse leaving the minimap. */
void ABoredPlayerController::MouseLeftMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}

/** Handler for mouse pressed over minimap. */
void ABoredPlayerController::MousePressedOverMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}

/** Handler for mouse release over minimap. */
void ABoredPlayerController::MouseReleasedOverMinimap()
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->EndSwipeNow();
	}
}

void ABoredPlayerController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{}
void ABoredPlayerController::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{}
void ABoredPlayerController::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{}
void ABoredPlayerController::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{}
void ABoredPlayerController::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{}
void ABoredPlayerController::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{}
void ABoredPlayerController::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{}
void ABoredPlayerController::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{}
void ABoredPlayerController::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{
	// Pass the pinch through to the camera component.
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchStarted(AnchorPosition1, AnchorPosition2, DownTime);
	}
}
void ABoredPlayerController::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{
	if (GetCameraComponent() != NULL)
	{
		GetCameraComponent()->OnPinchUpdate(InputHandler, ScreenPosition1, ScreenPosition2, DownTime);
	}
}