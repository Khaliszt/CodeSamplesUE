/* This is an Example of an easy accesor I made to apply a native UE4 feature for loading levels asynchronously and having your load screen unlocked
from the main thread. The code itself is partly Epic Games', and what I offer is an easy way of applying it as a module to your game.

This includes various files from your Custom Module's folder and the game's build files.
*/


/*
                         ========== IN YOUR GAME'S Build.cs FILE ==========
*/

using UnrealBuildTool;

public class YOURGAME : ModuleRules
{
	public YOURGAME(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" }); // TODO: Whatever extra stuff you have here

		PrivateDependencyModuleNames.AddRange(new string[] { "CUSTOMGameLoadingScreen" }); // TODO: Whatever extra stuff you have here
    }
}




/*
                         ========== CustomLoadingScreen.Build.cs ==========
*/

using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class CUSTOMGameLoadingScreen : ModuleRules
{
	public CUSTOMGameLoadingScreen(ReadOnlyTargetRules Target)
		: base(Target)
	{
		PrivatePCHHeaderFile = "Public/CUSTOMGameLoadingScreen.h"; // TODO: Actually whichever is your path inside the module's folder, most probably something like this

		PCHUsage = PCHUsageMode.UseSharedPCHs;

		PrivateIncludePaths.Add("CUSTOMGameLoadingScreen/Private");

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);
	}
}




/*
                         ========== Public/CUSTOMLoadingScreen.h ==========
*/

#pragma once

#include "ModuleInterface.h"
#include "Modules/ModuleManager.h"

/** Module interface for this game's loading screens */
class ICUSTOMGameLoadingScreenModule : public IModuleInterface
{
public:
	/** Loads the module so it can be turned on */
	static inline ICUSTOMGameLoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ICUSTOMGameLoadingScreenModule>("CUSTOMGameLoadingScreen");
	}

	/** Kicks off the loading screen for in game loading (not startup) */
	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) = 0;

	/** Stops the loading screen */
	virtual void StopInGameLoadingScreen() = 0;
};




/*
                         ========== Public/CUSTOMLoadingScreen.h ==========
*/

#include "CUSTOMGameLoadingScreen/Public/CUSTOMGameLoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "SThrobber.h"

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!
struct FCUSTOMLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FCUSTOMLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};

class SCUSTOMLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCUSTOMLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		// Load version of the logo with text baked in, path is hardcoded because this loads very early in startup
		static const FName LoadingScreenName(TEXT("/Game/ Path to your Texture"));

		LoadingScreenBrush = MakeShareable(new FCUSTOMLoadingScreenBrush(LoadingScreenName, FVector2D(1024, 256))); // Todo: Size you want
		
		FSlateBrush *BGBrush = new FSlateBrush();
		BGBrush->TintColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);

		ChildSlot
			[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)	
				.BorderImage(BGBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
					.Visibility(this, &SCUSTOMLoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const
	{
		bool Vis =  GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}
	
	/** Loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FCUSTOMGameLoadingScreenModule : public ICUSTOMGameLoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		// Force load for cooker reference
		LoadObject<UObject>(nullptr, TEXT("/Game/ Path to a Texture") );

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}
	
	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
		LoadingScreen.bWaitForManualStop = bPlayUntilStopped;
		LoadingScreen.bAllowEngineTick = bPlayUntilStopped;
		LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreen.WidgetLoadingScreen = SNew(SCUSTOMLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreen.WidgetLoadingScreen = SNew(SCUSTOMLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

};

IMPLEMENT_GAME_MODULE(FCUSTOMGameLoadingScreenModule, CUSTOMGameLoadingScreen);
