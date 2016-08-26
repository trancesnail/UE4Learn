// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredMiniMapCapture.h"
#include "BoredGameState.h"

ABoredMiniMapCapture::ABoredMiniMapCapture(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	GetCaptureComponent2D()->bCaptureEveryFrame = false;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	MiniMapWidth = 256;
	MiniMapHeight = 256;
	RootComponent->SetWorldRotation(FRotator(-90, 0, 0));
	AudioListenerGroundLevel = 500.0f;
	bUseAudioListenerOrientation = false;
	bTextureChanged = true;
}


void ABoredMiniMapCapture::BeginPlay()
{
	Super::BeginPlay();

	if (!GetCaptureComponent2D()->TextureTarget || MiniMapWidth != GetCaptureComponent2D()->TextureTarget->GetSurfaceWidth()
		|| MiniMapHeight != GetCaptureComponent2D()->TextureTarget->GetSurfaceHeight())
	{
		MiniMapView = NewObject<UTextureRenderTarget2D>();
		MiniMapView->InitAutoFormat(MiniMapWidth, MiniMapHeight);
		GetCaptureComponent2D()->TextureTarget = MiniMapView;
		bTextureChanged = true;
	}

	FRotator OriginalRotation = RootComponent->GetComponentRotation();
	RootComponent->SetWorldRotation(FRotator(-90.f, 0, OriginalRotation.Roll));
	ABoredGameState* const MyGameState = GetWorld()->GetGameState<ABoredGameState>();
	if (MyGameState != nullptr)
	{
		MyGameState->MiniMapCamera = this;
	}
	CachedFOV = GetCaptureComponent2D()->FOVAngle;
	CachedLocation = RootComponent->GetComponentLocation();
	UpdateWorldBounds();
}

void ABoredMiniMapCapture::Tick(float DeltaSeconds)
{
	if (CachedFOV != GetCaptureComponent2D()->FOVAngle || CachedLocation != RootComponent->GetComponentLocation() || bTextureChanged)
	{
		bTextureChanged = false;
		CachedFOV = GetCaptureComponent2D()->FOVAngle;
		CachedLocation = RootComponent->GetComponentLocation();
		UpdateWorldBounds();
	}
}

void ABoredMiniMapCapture::UpdateWorldBounds()
{
	ABoredGameState* const MyGameState = GetWorld()->GetGameState<ABoredGameState>();
	if (MyGameState != nullptr)
	{
		TArray<FVector> Points;
		FVector const CamLocation = RootComponent->GetComponentLocation();
		float DistanceFromGround = CamLocation.Z - GroundLevel;
		float Alpha = FMath::DegreesToRadians(GetCaptureComponent2D()->FOVAngle / 2);
		float MaxVisibleDistance = (DistanceFromGround / FMath::Cos(Alpha)) * FMath::Sin(Alpha);

		Points.Add(FVector(CamLocation.X + MaxVisibleDistance, CamLocation.Y + MaxVisibleDistance, GroundLevel));
		Points.Add(FVector(CamLocation.X - MaxVisibleDistance, CamLocation.Y - MaxVisibleDistance, GroundLevel));

		MyGameState->WorldBounds = FBox(Points);
		GetCaptureComponent2D()->UpdateContent();
	}
}

#if WITH_EDITOR
void ABoredMiniMapCapture::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	FName PropertyName = PropertyThatChanged != nullptr ? PropertyThatChanged->GetFName() : NAME_None;

	if (PropertyName == FName(TEXT("RelativeRotation")))
	{
		FRotator ChangedRotation = RootComponent->GetComponentRotation();
		RootComponent->SetWorldRotation(FRotator(-90, 0, ChangedRotation.Roll));
	}
}

void ABoredMiniMapCapture::EditorApplyRotation(const FRotator& DeltaRotation, bool bAltDown, bool bShiftDown, bool bCtrlDown)
{
	FRotator FiltredRotation(0, DeltaRotation.Yaw, 0);
	Super::EditorApplyRotation(FiltredRotation, bAltDown, bShiftDown, bCtrlDown);
}

#endif