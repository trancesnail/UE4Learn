// Fill out your copyright notice in the Description page of Project Settings.

#include "Bored.h"
#include "Boredstyle.h"


class FBoredGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		//Hot reload hack
		FSlateStyleRegistry::UnRegisterSlateStyle(FBoredStyle::GetStyleSetName());
		FBoredStyle::Initialize();
	}

	virtual void ShutdownModule() override
	{
		FBoredStyle::Shutdown();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FBoredGameModule, Bored, "Bored" );

DEFINE_LOG_CATEGORY(BoredGame)
DEFINE_LOG_CATEGORY(BoredGameInit)