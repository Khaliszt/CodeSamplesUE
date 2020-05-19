// Copyright @Khaliszt

// Header
#include "GameModeExample.h"

// YOURGAME
#include "YOURGAMEManager.h"

// ==== EXAMPLE CLASS ====
// CONSTRUCTOR
AGameModeExample::AGameModeExample()
{
	PrimaryActorTick.bCanEverTick = true; // TODO: Can be false too
	
	// Get and Set the YOURGAMEManager from the editor's BP Version
	static ConstructorHelpers::FClassFinder<AYOURGAMEManager> YOURGAMEManagerBPClass (TEXT("/Game/ Your Directory to the class in the Editor"));
	if (YOURGAMEManagerBPClass.Class != NULL)
	{
		YOURGAMEManagerClass = YOURGAMEManagerBPClass.Class;
	}
	// TODO: To use the C++ Class directly just use AYOURGAMEManager::StaticClass();
}

// EDITOR CONSTRUCTOR
AGameModeExample::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	// Spawn the EXAMPLE Manager Class
	YOURGAMEManager = GetWorld()->SpawnActor<AYOURGAMEManager>(YOURGAMEManagerClass);
}

void AGameModeExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// PRINT SCREEN: GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Turquoise, FString::SanitizeFloat(DeltaTime));
	// LOG MESSAGE: UE_LOG(YOURGAMEDebugLog, Log, TEXT("Delta Time is '%s'"), *FString::SanitizeFloat(DeltaTime));
}

void AGameModeExample::BeginPlay()
{
	Super::BegingPlay();
	
	// TODO: Read this from your Load file
	CurrentGameState = EGameState::Normal;
	
	// Do things like starting a Score List or loading characters in checkpoints
}

void AGameModeExample::SetGameState(EGameState NewGameState)
{
	if (NewGameState == NewGameState)
	{
		// No changes, leave.
		return;
	}
	
	// Set it
	CurrentGameState = NewGameState;
	
	// Broadcast it (Delegate declared in header)
	OnGameStateChanged.Broadcast(NewGameState);
}

EGameState AGameModeExample::GetGameState()
{
	return CurrentGameState;
}
