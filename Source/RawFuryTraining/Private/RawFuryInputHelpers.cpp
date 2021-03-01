// Fill out your copyright notice in the Description page of Project Settings.

#include "RawFuryInputHelpers.h"

#include "GameFramework/InputSettings.h"

void URawFuryInputHelpers::UpdateInputAction(FName ActionName, const FInputChord& Input)
{
    UInputSettings* InputSettings = UInputSettings::GetInputSettings();

    TArray<FInputActionKeyMapping> OutMappings;
    InputSettings->GetActionMappingByName(ActionName, OutMappings);

    for (const FInputActionKeyMapping& Mapping : OutMappings)
    {
        InputSettings->RemoveActionMapping(Mapping);
    }

    FInputActionKeyMapping NewInput(ActionName, Input.Key, Input.bShift, Input.bCtrl, Input.bAlt, Input.bCmd);
    InputSettings->AddActionMapping(NewInput);
}
