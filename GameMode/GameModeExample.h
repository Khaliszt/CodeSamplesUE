#pragma once

#include "YOURGAME.h"

#include "CoreMinimal.h"
#include "Queue.h"

#include "GameModeExample.generated.h"

// ==== EXAMPLE DELEGATE DECLARATION ====
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameState, NewGameState);

