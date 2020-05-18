// Header
#include "YOURGameManager.h"

// ENGINE
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// YOURGAME
#include "YOURGAME.h"
#include "GameModeExample.h"
#include "CustomActor.h"

void AYOURGAMEManager::BeginPlay()
{
  Super::BeginPlay();
  
  // Get Game Mode
  if(AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld()))
	{
    		 // Get Custom Game Mode
		 if(AGameModeExample* GameModeCast = Cast<AGameModeExample>(GameMode))
		 {
			CustomGameMode  = GameModeCast; // Declared in Header
			// Bind the Custom State
       			CustomGameMode->OnGameStateChanged.AddDynamic(this, &YOURGAMEManager::OnGameStateChanged);
		 }
	}
}

void AYOURGAMEManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
   Super::EndPlay(EndPlayReason);
   
   // Clean Set
   CustomActorsSet.Empty();
  
   // Null pointers
   CustomGameMode = nullptr;
}

void AYOURGAMEManager::RegisterCustomActor(ACustomActor* NewActor)
{
	if (!NewActor)
	{
		return;
	}
	
	if (!CustomActorsSet.Contains(ActorToErase)) // Not really needed as Add() has an internal check, but it's safer and avoids cascading.
	{
		CustomActorsSet.Add(NewActor);
	}
	
}
  
void AYOURGAMEManager::EraseCustomActor(ACustomActor* ActorToErase)
{
	if (!ActorToErase)
	{
		return;
	}
	
	CustomActorsSet.Remove(ActorToErase);

}
  
int AYOURGAMEManager::GetCustomActorsAmount()
{
	 return CustomActorsSet.Num();
}

void AYOURGAMEManager::OnGameStateChanged(EGameState NewGameState)
{
	CurrentGameState = NewGameState;
	
	// Do things based on the new Game State
}
