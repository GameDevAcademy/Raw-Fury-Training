// GameDev Academy 2021 - RawFury Training v1.0

#include "RawFuryInputHelpers.h"

#include "GameFramework/InputSettings.h"

void URawFuryInputHelpers::UpdateInputAction(FName ActionName, const FInputChord& Input)
{
    UInputSettings* InputSettings = UInputSettings::GetInputSettings();

    TArray<FInputActionKeyMapping> OutMappings;
    InputSettings->GetActionMappingByName(ActionName, OutMappings);

    for (const FInputActionKeyMapping& Mapping : OutMappings)
    {
        InputSettings->RemoveActionMapping(Mapping, false);
    }

    FInputActionKeyMapping NewInput(ActionName, Input.Key, Input.bShift, Input.bCtrl, Input.bAlt, Input.bCmd);
    InputSettings->AddActionMapping(NewInput, true);
}
