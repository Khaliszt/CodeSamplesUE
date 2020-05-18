// Header
#include "YOURGameManager.h"

// ENGINE
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// YOURGAME
#include "YOURGAME.h"
#include "GameModeExample.h"

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
