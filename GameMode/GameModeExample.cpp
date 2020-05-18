// Header
#include "GameModeExample.h"

// YOURGAME
#include "YOURGAMEManager.h"

// ==== EXAMPLE CLASS ====
// CONSTRUCTOR
AGameModeExample::AGameModeExample()
{
	PrimaryActorTick.bCanEverTick = true; // TODO: Can be false
	
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
	
	YOURGAMEManager = GetWorld()->SpawnActor<AYOURGAMEManager>(YOURGAMEManagerClass);
}

void AGameModeExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// PRINT SCREEN: GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Turquoise, FString::SanitizeFloat(DeltaTime));
	// LOG MESSAGE: UE_LOG(YOURGAMEDebugLog, Log, TEXT("Delta Time is '%s'"), *FString::SanitizeFloat(DeltaTime));
}
