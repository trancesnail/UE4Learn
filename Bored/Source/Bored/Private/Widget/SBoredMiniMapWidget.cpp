// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "SBoredMiniMapWidget.h"
#include "SlateOptMacros.h"

#include "BoredPlayerController.h"
#include "BoredHUD.h"
#include "BoredGameState.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBoredMiniMapWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill);
	OwnerHUD = InArgs._OwnerHUD;
	bIsMouseButtonDown = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION



FReply SBoredMiniMapWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (OwnerHUD.IsValid() == false)
	{
		return FReply::Unhandled();
	}
	ABoredPlayerController* const StrategyPlayerController = Cast<ABoredPlayerController>(GEngine->GetFirstLocalPlayerController(OwnerHUD.Get()->GetWorld()));
	if (StrategyPlayerController == nullptr)
	{
		return FReply::Unhandled();
	}
	ABoredGameState const* const MyGameState = StrategyPlayerController->GetWorld()->GetGameState<ABoredGameState>();
	ABoredHUD* HUD = Cast<ABoredHUD>(StrategyPlayerController->MyHUD);
	if ((MyGameState == nullptr) || (HUD == nullptr))
	{
		return FReply::Unhandled();
	}

	const float UIScale = HUD->UIScale;
	const float HalfMiniMapWidth = ((MyGameState->MiniMapCamera->MiniMapWidth - HUD->MiniMapMargin) * UIScale) / 2.0f;
	const float HalfMiniMapHeight = ((MyGameState->MiniMapCamera->MiniMapHeight - HUD->MiniMapMargin) * UIScale) / 2.0f;
	const float BaseRotation = 270.0f;

	FVector2D LocalCoords(MouseEvent.GetScreenSpacePosition() - MyGeometry.AbsolutePosition);
	FVector2D NormalizedMinimapCoords(((LocalCoords.X - HalfMiniMapWidth) / HalfMiniMapWidth), ((LocalCoords.Y - HalfMiniMapHeight) / HalfMiniMapHeight));

	const FRotator Rot = FRotator(0.f, BaseRotation + MyGameState->MiniMapCamera->GetRootComponent()->GetComponentRotation().Roll, 0.f);
	const FRotationMatrix RotationMatrix(Rot);
	const FVector OrgCenter = MyGameState->WorldBounds.GetCenter();
	const FVector OrgExt = MyGameState->WorldBounds.GetExtent();
	const FVector Extent = RotationMatrix.TransformPosition(FVector(NormalizedMinimapCoords, 0)) * OrgExt;

	FVector CameraTarget = FVector(OrgCenter.X - Extent.X, OrgCenter.Y - Extent.Y, OrgCenter.Z + Extent.Z);

	StrategyPlayerController->MousePressedOverMinimap();
	StrategyPlayerController->SetCameraTarget(CameraTarget);

	bIsMouseButtonDown = true;
	return FReply::Handled();
}

void SBoredMiniMapWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	bIsMouseButtonDown = false;
	ABoredPlayerController* const PlayerController = Cast<ABoredPlayerController>(GEngine->GetFirstLocalPlayerController(OwnerHUD.Get()->GetWorld()));
	if (PlayerController != NULL)
	{
		PlayerController->MouseLeftMinimap();
	}
}

FReply SBoredMiniMapWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();
	// Only handle UP if we handled DOWN
	if (bIsMouseButtonDown == true)
	{
		bIsMouseButtonDown = false;
		ABoredPlayerController* const PlayerController = Cast<ABoredPlayerController>(GEngine->GetFirstLocalPlayerController(OwnerHUD.Get()->GetWorld()));
		if (PlayerController != NULL)
		{
			PlayerController->MouseReleasedOverMinimap();
		}
		Reply = FReply::Handled();
	}
	return Reply;
}

FReply SBoredMiniMapWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bIsMouseButtonDown)
	{
		OnMouseButtonDown(MyGeometry, MouseEvent);
	}
	return FReply::Handled();
}

int32 SBoredMiniMapWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	if (OwnerHUD.IsValid() == true)
	{
		ABoredPlayerController* const PC = Cast<ABoredPlayerController>(GEngine->GetFirstLocalPlayerController(OwnerHUD.Get()->GetWorld()));
		ABoredGameState const* const MyGameState = PC && PC->GetWorld() ? PC->GetWorld()->GetGameState<ABoredGameState>() : NULL;
		ABoredHUD* const HUD = PC ? Cast<ABoredHUD>(PC->MyHUD) : NULL;
		if (MyGameState && MyGameState->MiniMapCamera.IsValid() && HUD)
		{
			TArray<FVector2D> LinePoints;
			const float HalfMiniMapWidth = (MyGameState->MiniMapCamera->MiniMapWidth - HUD->MiniMapMargin) / 2.0f;
			const float HalfMiniMapHeight = (MyGameState->MiniMapCamera->MiniMapHeight - HUD->MiniMapMargin) / 2.0f;
			const FVector2D MiniMapCenter(HalfMiniMapWidth, HalfMiniMapHeight);

			for (int32 i = 0; i < 5; i++)
			{
				LinePoints.Add(MiniMapCenter + HUD->MiniMapPoints[i % 4] * MiniMapCenter);
			}

			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				LinePoints,
				MyClippingRect,
				bParentEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
				FColor::White,
				false);
		}
	}
	return LayerId;
}
