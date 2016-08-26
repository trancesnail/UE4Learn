// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Widgets/SCompoundWidget.h"
class ABoredHUD;
class SBoredMiniMapWidget;

/**
 * 
 */
class BORED_API SBoredHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBoredHUDWidget) : _OwnerHUD()
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<ABoredHUD>, OwnerHUD)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	/** executed on every frame */
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;


	/** current UI scale attribute */
	TAttribute<float> UIScale;

	/** gets mini map width */
	FOptionalSize GetMiniMapWidth() const;

	/** gets mini map height */
	FOptionalSize GetMiniMapHeight() const;

	/** margin for border */
	float MiniMapBorderMargin;

	/** Pointer to our parent HUD */
	TWeakObjectPtr<ABoredHUD> OwnerHUD;

	/** style for this HUD */
	const struct FBoredHUDStyle* HUDStyle;

	/** if console is currently opened */
	bool bConsoleVisible;

	/** minimap widget */
	TSharedPtr<SBoredMiniMapWidget> MiniMapWidget;

	/** gets current scale for drawing menu */
	float GetUIScale() const;

	/** sets hit test invisibility when console is up */
	EVisibility GetSlateVisibility() const;
};

