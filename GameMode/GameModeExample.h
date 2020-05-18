#pragma once

#include "YOURGAME.h"

#include "CoreMinimal.h"
#include "Queue.h"

#include "GameModeExample.generated.h"

// YOURGAME
#include "AYOURGAMEManagerClass.h"

// ==== EXAMPLE DELEGATE DECLARATION ====
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameState, NewGameState); // ENUM declared in YOURGAME.h !! 

// ==== EXAMPLE CLASS ====
UCLASS()
class YOURGAME_API AGameModeExample : public AGameModeBase
{
	GENERATED_BODY()

// ENGINE 
//========
	
public:

AGameModeExample();

virtual void OnConstruction(const FTransform& Transform) override;

protected:

virtual void Tick(float DeltaTime) override;

virtual void BeginPlay() override;
  
private:

// YOURGAME METHODS
//==================
public:
void SetGameState(EGameState NewGameState);
EGameState GetGameState();

// YOURGAME MEMBERS
//==================
public:
// STATES
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeExample|States")
EGameState CurrentGameState = EGameState::Normal;

// Managers
UPROPERTY(Transient)
class AYOURGAMEManagerClass* YOURGAMEManager = nullptr;

protected:
private:
