// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BoredPlayerController.generated.h"

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

	/** Handler for mouse leaving the minimap. */
	void MouseLeftMinimap();

	/** Handler for mouse pressed over minimap. */
	void MousePressedOverMinimap();

	/** Handler for mouse release over minimap. */
	void MouseReleasedOverMinimap();
	
	
};
