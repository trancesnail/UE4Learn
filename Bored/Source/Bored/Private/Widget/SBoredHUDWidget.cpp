// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "SBoredHUDWidget.h"
#include "SlateOptMacros.h"

#include "BoredHUDWidgetStyle.h"
#include "BoredStyle.h"
#include "SBoredMiniMapWidget.h"
#include "Engine/Console.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBoredHUDWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
		.ButtonStyle(&HUDStyle->MenuButtonStyle)
	];
	*/

	HUDStyle = &FBoredStyle::Get().GetWidgetStyle<FBoredHUDStyle>("BoredHUDStyle");
	OwnerHUD = InArgs._OwnerHUD;
	//Visibility.Bind(this, &SBoredHUDWidget::GetSlateVisibility);
	Visibility = EVisibility::Visible;
	UIScale.Bind(this, &SBoredHUDWidget::GetUIScale);
	MiniMapBorderMargin = 20;
	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SDPIScaler)
		.DPIScale(UIScale)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(FMargin(MiniMapBorderMargin, 0, 0, MiniMapBorderMargin))
			[
				SNew(SButton)
				.ContentPadding(FMargin(150, 50))
				.ContentScale(FVector2D(20,30))
				.TextStyle(&HUDStyle->TextBlockStyle)
				.Text(FText::FromString(TEXT("我是一个按钮！")))
			]

			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Left)
			.Padding(FMargin(MiniMapBorderMargin, 0, 0, MiniMapBorderMargin))
			[
				SNew(SBorder)
				.BorderImage(&HUDStyle->MinimapFrameBrush)
				.Padding(FMargin(0))
				[
					SNew(SBox)
					.Padding(FMargin(MiniMapBorderMargin, MiniMapBorderMargin))
					.WidthOverride(this, &SBoredHUDWidget::GetMiniMapWidth)
					.HeightOverride(this, &SBoredHUDWidget::GetMiniMapHeight)
					[
						SAssignNew(MiniMapWidget, SBoredMiniMapWidget)
						.OwnerHUD(OwnerHUD)
					]
				]
			]
		]
	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


/** gets mini map width */
FOptionalSize SBoredHUDWidget::GetMiniMapWidth() const
{
	float Result = 0.0f;
	ABoredGameState const* const MyGameState = OwnerHUD->GetWorld()->GetGameState<ABoredGameState>();
	if (MyGameState && MyGameState->MiniMapCamera.IsValid())
	{
		Result = MyGameState->MiniMapCamera->MiniMapWidth;
	}
	return Result;
}

/** gets mini map height */
FOptionalSize SBoredHUDWidget::GetMiniMapHeight() const
{
	float Result = 0.0f;
	ABoredGameState const* const MyGameState = OwnerHUD->GetWorld()->GetGameState<ABoredGameState>();
	if (MyGameState && MyGameState->MiniMapCamera.IsValid())
	{
		Result = MyGameState->MiniMapCamera->MiniMapHeight;
	}
	return Result;
}

/** gets current scale for drawing menu */
float SBoredHUDWidget::GetUIScale() const
{
	float Result = 0.5f;
	if (GEngine && GEngine->GameViewport)
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		Result = ViewportSize.X / 2048.0f;
	}
	//as a fall back assume 1024x768
	return Result;
}

/** sets hit test invisibility when console is up */
EVisibility SBoredHUDWidget::GetSlateVisibility() const
{
	return bConsoleVisible ? EVisibility::HitTestInvisible : EVisibility::Visible;
}

void SBoredHUDWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	//ugly code seeing if the console is open
	UConsole* ViewportConsole = (GEngine != NULL && GEngine->GameViewport != NULL) ? GEngine->GameViewport->ViewportConsole : NULL;
	if (ViewportConsole != NULL && (ViewportConsole->ConsoleState == "Typing" || ViewportConsole->ConsoleState == "Open"))
	{
		if (!bConsoleVisible)
		{
			bConsoleVisible = true;
			FSlateApplication::Get().SetAllUserFocusToGameViewport();
		}
	}
	else
	{
		if (bConsoleVisible)
		{
			bConsoleVisible = false;
			FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
		}
	}
}