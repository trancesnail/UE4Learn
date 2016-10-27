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

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / "Slate"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )

TSharedRef< FSlateStyleSet > FBoredStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FBoredStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	FSlateStyleSet& Style = StyleRef.Get();

	const FLinearColor GoldColor(FColor(255, 213, 160));

	// Fonts still need to be specified in code for now
	Style.Set("StrategyGame.MenuFont", TTF_FONT("Fonts/Roboto-Black", 32));

	Style.Set("StrategyGame.ResourcesTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 40))
		.SetColorAndOpacity(GoldColor)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetShadowOffset(FIntPoint(-1, 1))
		);

	Style.Set("StrategyGame.ButtonFont", TTF_FONT("Fonts/Roboto-Black", 18));
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