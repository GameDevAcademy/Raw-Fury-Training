// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RawFuryInputHelpers.generated.h"

/**
 * 
 */
UCLASS()
class URawFuryInputHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = RawFury)
	static void UpdateInputAction(FName ActionName, const FInputChord& Input);
};
