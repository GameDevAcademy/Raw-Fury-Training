// Fill out your copyright notice in the Description page of Project Settings.

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
