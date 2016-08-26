// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "BoredHUDWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct BORED_API FBoredHUDStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FBoredHUDStyle();
	virtual ~FBoredHUDStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FBoredHUDStyle& GetDefault();


	/**
	* The brush used to draw the frame around the mini-map
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush MinimapFrameBrush;
	FBoredHUDStyle& SetMinimapFrameBrush(const FSlateBrush& InMinimapFrameBrush) { MinimapFrameBrush = InMinimapFrameBrush; return *this; }

	// Style that define the appearance of all menu buttons. 
	UPROPERTY(EditAnywhere, Category = Appearance)
	FButtonStyle MenuButtonStyle;

	// Style that define the appearance of all menu buttons. 
	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle TextBlockStyle;

};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UBoredHUDWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FBoredHUDStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
