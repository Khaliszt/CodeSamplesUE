// Copyright @Khaliszt

// Header
#include "GameMode/CustomActor/CustomActor.h"

// ENGINE

// YOURGAME
#include "GameMode/ManagerClass/YOURGAMEManager.h"
#include "GameMode/GameModeExample.h"
#include "ExampleLibrary/ExampleLibrary.h"

void ACustomActor::BeginPlay()
{
  	Super::BeginPlay();
  
  	// Get Game Mode
	if(AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld()))
	{
    		// Get Custom Game Mode
		if(AGameModeExample* GameModeCast = Cast<AGameModeExample>(GameMode))
		{
			GameMode  = GameModeCast; // Declared in Header
        
        		// Add this custom actor to the register of actors in the MANAGER (For whatever use)
			GameMode->YOURGAMEManagerClass->RegisterCustomActor(this); 
       
       		  	// COULD ALSO: CustomGameMode->OnGameStateChanged.AddDynamic(this, &ACustomActor::OnGameStateChanged);
		}
	}
  
  // Example use of the LIBRARY --> ExampleLibrary::FindBestComponentTowardsDirection()
  // i.e. Get something close to the aiming direction of this actor.
}
