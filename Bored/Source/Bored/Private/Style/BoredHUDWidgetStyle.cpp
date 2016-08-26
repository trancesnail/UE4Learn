// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredHUDWidgetStyle.h"


FBoredHUDStyle::FBoredHUDStyle()
{
}

FBoredHUDStyle::~FBoredHUDStyle()
{
}

const FName FBoredHUDStyle::TypeName(TEXT("FBoredHUDStyle"));

const FBoredHUDStyle& FBoredHUDStyle::GetDefault()
{
	static FBoredHUDStyle Default;
	return Default;
}

void FBoredHUDStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them

	OutBrushes.Add(&MinimapFrameBrush);

}


UBoredHUDWidgetStyle::UBoredHUDWidgetStyle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}