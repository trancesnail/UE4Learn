// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredHUD.h"
#include "BoredGameState.h"
#include "BoredPlayerController.h"
#include "SBoredHUDWidget.h"
#include "BoredHelpers.h"

ABoredHUD::ABoredHUD(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	MiniMapMargin = 40;
}


void ABoredHUD::DrawHUD()
{
	if (GEngine && GEngine->GameViewport)
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		UIScale = ViewportSize.X / 2048.0f;
	}

	Super::DrawHUD();
	bool bConsoleOpen = false;

	ABoredGameState const* const MyGameState = GetWorld()->GetGameState<ABoredGameState>();
	if (MyGameState)
	{
		BuildMenuWidgets();
		DrawMiniMap();
	}
}

void ABoredHUD::TogglePauseMenu()
{
	//if (MyBoredHUDWidget.IsValid())
	//{
	//	MyBoredHUDWidget->TogglePauseMenu();
	//}
}

void ABoredHUD::DrawMiniMap()
{
	const ABoredPlayerController* const PC = Cast<ABoredPlayerController>(PlayerOwner);
	ABoredGameState const* const MyGameState = GetWorld()->GetGameState<ABoredGameState>();

	// @todo, clean this up
	if (PC && MyGameState && MyGameState->MiniMapCamera.IsValid())
	{
		const float BaseRotation = 270;
		UTexture* MiniMapTexture = Cast<UTexture>(MyGameState->MiniMapCamera->GetCaptureComponent2D()->TextureTarget);
		const float MapWidth = (MyGameState->MiniMapCamera->MiniMapWidth - MiniMapMargin) * UIScale;
		const float MapHeight = (MyGameState->MiniMapCamera->MiniMapHeight - MiniMapMargin) * UIScale;
		const FVector WorldCenter = MyGameState->WorldBounds.GetCenter();
		const FVector WorldExtent = MyGameState->WorldBounds.GetExtent();
		const FRotator RotOrg = MyGameState->MiniMapCamera->GetCaptureComponent2D()->GetComponentRotation();
		const FRotationMatrix RotationMatrix(FRotator(0, BaseRotation - RotOrg.Roll, 0));
		const FVector2D Offset(MiniMapMargin * UIScale + (MapWidth / 2.0f), Canvas->ClipY - (MapHeight / 2.0f) - MiniMapMargin * UIScale);

		if (MiniMapTexture)
		{
			FCanvasTileItem MapTileItem(FVector2D(0.0f, 0.0f), FVector2D(0.0f, 0.0f), FLinearColor::White);
			MapTileItem.Texture = MiniMapTexture->Resource;
			MapTileItem.Size = FVector2D(MapWidth, MapHeight);
			MapTileItem.BlendMode = SE_BLEND_Opaque;
			Canvas->DrawItem(MapTileItem, FVector2D(MiniMapMargin * UIScale, Canvas->ClipY - MapHeight - MiniMapMargin * UIScale));
		}
		FCanvasTileItem TileItem(FVector2D(0.0f, 0.0f), FVector2D(0.0f, 0.0f), FLinearColor::White);
		TileItem.Size = FVector2D(6 * UIScale, 6 * UIScale);
		//for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
		//{
		//	AStrategyChar* TestChar = Cast<AStrategyChar>(*Iterator);
		//	if (TestChar != NULL && TestChar->GetHealth() > 0)
		//	{
		//		AStrategyAIController* AIController = Cast<AStrategyAIController>(TestChar->Controller);
		//		if (AIController != NULL && AIController->IsLogicEnabled())
		//		{
		//			FLinearColor DrawColor;
		//			if (PC != NULL && TestChar->GetTeamNum() == PC->GetTeamNum())
		//			{
		//				DrawColor = FColor(49, 137, 253, 255);
		//			}
		//			else
		//			{
		//				DrawColor = FColor(242, 114, 16, 255);
		//			}
		//			const FVector CenterRelativeLocation = RotationMatrix.TransformPosition(TestChar->GetActorLocation() - WorldCenter);
		//			const FVector2D MiniMapPoint = FVector2D(CenterRelativeLocation.X / WorldExtent.X, CenterRelativeLocation.Y / WorldExtent.Y);
		//			TileItem.SetColor(DrawColor);
		//			Canvas->DrawItem(TileItem, FVector2D(Offset.X + MiniMapPoint.X * (MapWidth / 2.0f), Offset.Y + MiniMapPoint.Y * (MapHeight / 2.0f)));
		//		}
		//	}
		//}


		ULocalPlayer* MyPlayer = Cast<ULocalPlayer>(PC->Player);
		FVector2D ScreenCorners[4] = { FVector2D(0, 0), FVector2D(Canvas->ClipX, 0), FVector2D(Canvas->ClipX, Canvas->ClipY), FVector2D(0, Canvas->ClipY) };
		const FPlane GroundPlane = FPlane(FVector(0, 0, MyGameState->WorldBounds.Max.Z), FVector::UpVector);
		for (int32 i = 0; i < 4; i++)
		{
			FVector RayOrigin, RayDirection;
			FBoredHelpers::DeprojectScreenToWorld(ScreenCorners[i], MyPlayer, RayOrigin, RayDirection);
			const FVector GroundPoint = FBoredHelpers::IntersectRayWithPlane(RayOrigin, RayDirection, GroundPlane);
			const FVector CenterRelativeLocation = RotationMatrix.TransformPosition(GroundPoint - WorldCenter);
			MiniMapPoints[i] = FVector2D(CenterRelativeLocation.X / WorldExtent.X, CenterRelativeLocation.Y / WorldExtent.Y);
		}
	}
}

void ABoredHUD::BuildMenuWidgets()
{
	if (!GEngine || !GEngine->GameViewport)
	{
		return;
	}

	if (!MyBoredHUDWidget.IsValid())
	{
		const ABoredPlayerController* PCOwner = Cast<ABoredPlayerController>(PlayerOwner);

		if (PCOwner)
		{
			SAssignNew(MyBoredHUDWidget, SBoredHUDWidget)
				.OwnerHUD(this);
			// Setup the widget to forward focus to when the viewport receives focus.

			if (MyBoredHUDWidget.IsValid())
			{

				GEngine->GameViewport->AddViewportWidgetContent(
					SNew(SWeakWidget)
					.PossiblyNullContent(MyBoredHUDWidget.ToSharedRef())
					);
			}

			TSharedPtr<SViewport> GameViewportWidget = GEngine->GetGameViewportWidget();
			if (GameViewportWidget.IsValid())
			{
				GameViewportWidget->SetWidgetToFocusOnActivate(MyBoredHUDWidget);
			}
		}
	}
}