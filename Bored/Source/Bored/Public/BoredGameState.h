// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "BoredMiniMapCapture.h"
#include "BoredGameState.generated.h"

/**
 * 
 */
UCLASS()
class BORED_API ABoredGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

public:
	/** Mini map camera component. */
	TWeakObjectPtr<ABoredMiniMapCapture> MiniMapCamera;

	/** World bounds for mini map & camera movement. */
	FBox WorldBounds;
	
};
