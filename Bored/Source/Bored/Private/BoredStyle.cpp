// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "BoredStyle.h"
#include "SlateGameResources.h"

TSharedPtr< FSlateStyleSet > FBoredStyle::StrategyStyleInstance = NULL;

void FBoredStyle::Initialize()
{
	if (!StrategyStyleInstance.IsValid())
	{
		StrategyStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StrategyStyleInstance);
	}
}

void FBoredStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StrategyStyleInstance);
	ensure(StrategyStyleInstance.IsUnique());
	StrategyStyleInstance.Reset();
}

FName FBoredStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BoredStyle"));
	return StyleSetName;
}


TSharedRef< FSlateStyleSet > FBoredStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FBoredStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	FSlateStyleSet& Style = StyleRef.Get();

	const FLinearColor GoldColor(FColor(255, 213, 160));

	return StyleRef;
}


void FBoredStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FBoredStyle::Get()
{
	return *StrategyStyleInstance;
}