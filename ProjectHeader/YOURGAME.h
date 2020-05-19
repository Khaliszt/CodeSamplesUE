// Copyright @Khaliszt

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "YOURGAME.generated.h"

// EXAMPLE MACROS
#define DEBUG_PRINT(Time, Color, Text)	if(GEngine){GEngine->AddOnScreenDebugMessage(-1, Time, Color, Text);}
// #define DEBUG_LOG(Text, ...) UE_LOG(RATSDebugLog, Log, Text, ...)

#define TEST_BIT(Bitmask, Bit) (((Bitmask) & (1 << static_cast<uint8>(Bit))) > 0)
#define SET_BIT(Bitmask, Bit) (Bitmask |= 1 << static_cast<uint8>(Bit))
#define CLEAR_BIT(Bitmask, Bit) (Bitmask &= ~(1 << static_cast<uint8>(Bit)))

#define START_BITMASK_SWITCH(x) \ for (uint8 bit = 1; x >= bit; bit *= 2) if (x & bit) switch (bit)

// EXAMPLE Object Channels Definitions
#define ECC_Something		  	ECC_GameTraceChannel1 // Values According to Project's DefaultEngine.ini file 
#define ECC_AnotherThing		ECC_GameTraceChannel2
// todo ...

// ==== EXAMPLE Trace Channels ====
#define ECC_CoolChannel			ECC_GameTraceChannel3 // Values According to Project Project's DefaultEngine.ini file
#define ECC_SucksChannel		ECC_GameTraceChannel4
// todo ...

// ==== EXAMPLE Surface Types ====
#define EPST_BasicFloor			SurfaceType1
#define EPST_FancyFloor			SurfaceType2
// todo ...

// ==== EXAMPLE LOGS ====
// Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(YOURGAMECriticalErrorsLog, Fatal, All);

// Logging for Debug stuff. 
DECLARE_LOG_CATEGORY_EXTERN(YOURGAMEDebugLog, Log, All);

// ==== EXAMPLE ENUMS ====
UENUM(BlueprintType)
enum class EYourNewEnum : uint8 // Todo: I like to use uint8, in case I need conversions or comparisons
{
	YNE_FirstEntry		UMETA(DisplayName = "First"),
	YNE_SecondEntry		UMETA(DisplayName = "Second"),
	YNE_ThirdEntry		UMETA(DisplayName = "Third"),
	YNE_FourthEntry		UMETA(DisplayName = "Fourth"),
	YNE_MAX 		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EGameState : uint8
{
	GS_Basic		UMETA(DisplayName = "Basic"),
	GS_Altered		UMETA(DisplayName = "Altered"),
	GS_MAX			UMETA(Hidden)
};

// ==== EXAMPLE STRUCT ====
USTRUCT(BlueprintType)
struct FYourNewStruct : public FTableRowBase // This struct can be used with DATA TABLES
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FirstValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SecondValue;

  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = "true")) // This transform's Location will be editable within the editor
  	FTransform Transform;
  
 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
  	int32 ID;
  
  	FYourNewStruct()
  	{
    		FirstValue = 1.f;
    		SecondValue = 2.f;
    		Transform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector);
    		ID = 0;
  	}
};
