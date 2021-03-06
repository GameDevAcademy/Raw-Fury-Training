// GameDev Academy 2021 - RawFury Training v1.0

#include "RawFuryPlayerController.h"

#include "RawFuryTrainingGameMode.h"

#include "Kismet/GameplayStatics.h"

bool ARawFuryPlayerController::ShouldTakeControllerInput() const
{
    if (AGameModeBase* BaseGameMode = UGameplayStatics::GetGameMode(GetWorld()))
    {
        if (ARawFuryTrainingGameMode* GameMode = Cast<ARawFuryTrainingGameMode>(BaseGameMode))
        {
            return !GameMode->IsPlayingMobile();
        }
    }

    return true;
}

void ARawFuryPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    if (!ShouldTakeControllerInput() && IsFirstPawn(aPawn))
    {
        OnPlayersConnected();
    }
}

void ARawFuryPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    if (!ShouldTakeControllerInput() && IsFirstPawn(GetPawn()))
    {
        OnPlayersInputTick();
    }
}

bool ARawFuryPlayerController::IsFirstPawn(APawn* aPawn) const
{
    if (APlayerController* FirstPlayerController = UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0))
    {
        return aPawn == FirstPlayerController->GetPawn();
    }

    return false;
}
