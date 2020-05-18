// Header
#include "GameModeExample.h"

// YOURGAME
#include "YOURGAMEManager.h"

// ==== EXAMPLE CLASS ====
ARATSGameModeGameplay::ARATSGameModeGameplay()
{
	PrimaryActorTick.bCanEverTick = true; // TODO: Can be false
	
	// Get and Set the YOURGAMEManager from the editor's BP Version
	static ConstructorHelpers::FClassFinder<AYOURGAMEManager> YOURGAMEManagerBPClass (TEXT("/Game/ Your Directory to the class in the Editor"));
	if (YOURGAMEManagerBPClass.Class != NULL)
	{
		DefaultPawnClass = YOURGAMEManagerBPClass.Class;
}
