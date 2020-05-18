// Copyright @Khaliszt

// YOURGAME
#include "YOURGAME.h"

// Forward Declarations
class AGameModeExample;
class AYOURGAMEManager;
  
UCLASS()
class YOURGAME_API ACustomActor : public AActor
{
  GENERATED_BODY()
  
// ENGINE METHODS
//================
public:
  void BeginPlay() override;
 
// YOURGAME METHODS
//==================

// YOURGAME MEMBERS
//==================
protected:

// REFERENCES
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="ACustomActor|References")
AYOURGAMEManager* GameManager = nullptr;

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="ACustomActor|References")
AGameModeExample* GameMode = nullptr;
};
