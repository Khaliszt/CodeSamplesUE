// YOURGAME
#include "YOURGAME.h"

// Forward Declarations
class ACustomActor;
class AGameModeExample;
  
UCLASS()
class YOURGAME_API AYOURGAMEManager : public AActor
{
  GENERATED_BODY()
  
// ENGINE METHODS
//================
public:
  void BeginPlay() override;
  
  void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
  
  void OnConstruction();
  
// YOURGAME METHODS
//==================
public:
  UFUNCTION(BlueprintCallable, Category = "YOURGAMEManager|Management")
  void RegisterCustomActor(ACustomActor* NewActor);
  
  UFUNCTION(BlueprintCallable, Category = "YOURGAMEManager|Management")
  void EraseCustomActor(ACustomActor* ActorToErase);
  
  UFUNCTION(BlueprintCallable, BlueprintPure, Category = "YOURGAMEManager|Getters")
  int GetCustomActorsAmount();
  
protected:
  virtual void OnGameStateChanged(EGameState NewGameState);

// YOURGAME MEMBERS
//==================
public:

protected:
  // STATES
  EGameState CurrentGameState;
  
  // REFERENCES
  UPROPERTY(Transient)
  AGameModeExample* CustomGameMode = nullptr;
  
  // OTHERS
  TSet<ACustomActor> CustomActorsSet;

};
