// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BoredPlayerController.generated.h"

class ABoredSpectatorPawn;
class UBoredCameraComponent;

class UBoredInput;
/**
 * 
 */
UCLASS()
class BORED_API ABoredPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

protected:

	/** update input detection */
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

public:

	/** set desired camera position. */
	void SetCameraTarget(const FVector& CameraTarget);

	/** helper function to toggle input detection. */
	void SetIgnoreInput(bool bIgnore);

	/** Input handlers. */
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime);
	void OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	/** Toggles the ingame menu display. */
	void OnToggleInGameMenu();

	/** Handler for mouse leaving the minimap. */
	void MouseLeftMinimap();

	/** Handler for mouse pressed over minimap. */
	void MousePressedOverMinimap();

	/** Handler for mouse release over minimap. */
	void MouseReleasedOverMinimap();

	UPROPERTY()
	UBoredInput* InputHandler;

private:
	/** Helper to return cast version of Spectator pawn. */
	ABoredSpectatorPawn* GetBoredSpectatorPawn() const;
	
	/** Helper to return camera component via spectator pawn. */
	UBoredCameraComponent* GetCameraComponent() const;


};
