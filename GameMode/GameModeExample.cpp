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
		YOURGAMEManager = YOURGAMEManagerBPClass.Class;
	}
}

// EDITOR CONSTRUCTOR
AGameModeExample::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AGameModeExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Turquoise, FString::SanitizeFloat(DeltaTime));
	// UE_LOG(YOURGA);
}
