// Copyright @Khaliszt

#pragma once

#include "YOURGAME.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExampleLibrary.generated.h"

// Structure designed for the return types of some functions of the ExampleLibrary. 
USTRUCT(BlueprintType)
struct FComparisonFunctionsHelper
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly)
	UPrimitiveComponent* Component;

	UPROPERTY(BlueprintReadOnly)
	float FloatValue;

};

UCLASS()
class YOURGAME_API UExampleLibrary : public UObject
{
	GENERATED_BODY()
	
public: 

UFUNCTION(BlueprintCallable)
static void PlayAudioComponentSound(class UAudioComponent* AudioComponent, class USoundBase* Sound, float StartTime, bool bFadePrevious = false, float FadeTime = 0.15f, float FadeLevel = 0.f);

/* Finds the best component compared to the inputed direction. Must have a context location (from which to compare).
 *@param ComparedDirection is the direction you want to compare to.
 *@param ContextLocation is the context location to create a direction to compare from. 
 *@param ComparedComponents is the set of components you want to compare.
*/
UFUNCTION(BlueprintCallable)
static FComparisonFunctionsHelper FindBestComponentTowardsDirection(
								const FVector& ComparedDirection,
								const FVector& ContextLocation,
								const TSet<UPrimitiveComponent*>& ComparedComponents);
                
};

