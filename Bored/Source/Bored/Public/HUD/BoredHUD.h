// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "BoredHUD.generated.h"

class SBoredHUDWidget;
/**
 * 
 */
UCLASS()
class BORED_API ABoredHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
	
public:

	// Begin HUD interface
	virtual void DrawHUD() override;
	// End HUD interface

public:
	/** mini map margin */
	float MiniMapMargin;

	/** minimap frustum points */
	FVector2D MiniMapPoints[4];

	/** current UI scale */
	float UIScale;

protected:

	/** draws mini map */
	void DrawMiniMap();
	
	/** builds the slate widgets */
	void BuildMenuWidgets();

	/** HUD menu widget */
	TSharedPtr<class SBoredHUDWidget> MyBoredHUDWidget;
};
