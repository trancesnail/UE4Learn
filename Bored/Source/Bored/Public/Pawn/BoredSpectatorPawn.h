// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "BoredSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BORED_API ABoredSpectatorPawn : public ASpectatorPawn
{
	GENERATED_UCLASS_BODY()
	
	// Begin ADefaultPawn interface

	/** event call on move forward input */
	virtual void MoveForward(float Val) override;

	/** event call on strafe right input */
	virtual void MoveRight(float Val) override;

	/** Add custom key bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// End ADefaultPawn interface

	// The camera component for this camera
private:
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoredCameraComponent* BoredCameraComponent;
public:

	/** Handles the mouse scrolling down. */
	void OnMouseScrollUp();

	/** Handles the mouse scrolling up. */
	void OnMouseScrollDown();

	/* Returns a pointer to the strategy camera component the pawn has. */
	UBoredCameraComponent* GetBoredCameraComponent();
	
	
};
