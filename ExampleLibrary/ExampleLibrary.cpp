// Copyright @Khaliszt

// Header file
#include "ExampleLibrary.h"

// Engine
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


void UExampleLibrary::PlayAudioComponentSound(UAudioComponent* AudioComponent, USoundBase* Sound, const float StartTime, const bool bFadePrevious, const float FadeTime, const float FadeLevel)
{
	if (AudioComponent && Sound)
	{
		if (bFadePrevious)
		{
			AudioComponent->FadeOut(FadeTime, FadeLevel);
		}
		AudioComponent->SetSound(Sound);
		AudioComponent->Play(StartTime);
	}
}

FComparisonFunctionsHelper UExampleLibrary::FindBestComponentTowardsDirection(const FVector& ComparedDirection,
	const FVector& ContextLocation, const TSet<UPrimitiveComponent*>& ComparedComponents)
{
	{
		FComparisonFunctionsHelper StructReturn;
		float BestDirection = 0.0f;
		float IterationDot = 0.0f;
		UPrimitiveComponent* BestComponent = nullptr;

		for (UPrimitiveComponent* IndexedComponent : ComparedComponents)
		{
			if (IndexedComponent)
			{
				FVector IterationDirection = FVector(IndexedComponent->GetComponentLocation() - ContextLocation).GetSafeNormal();
				IterationDot = FVector::DotProduct(ComparedDirection, IterationDirection);
				if(IterationDot > BestDirection)
				{
					BestDirection = IterationDot;
					BestComponent = IndexedComponent;
				}							
			}
		}
		StructReturn.Component = BestComponent;
		StructReturn.FloatValue = BestDirection;
		return StructReturn;
	}
}
