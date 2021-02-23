// Fill out your copyright notice in the Description page of Project Settings.

#include "RawFuryPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ARawFuryPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    if (IsFirstPawn(aPawn))
    {
        OnPlayersConnected();
    }
}

void ARawFuryPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    if (IsFirstPawn(GetPawn()))
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
