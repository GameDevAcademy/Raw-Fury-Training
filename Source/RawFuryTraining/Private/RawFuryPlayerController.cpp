// Fill out your copyright notice in the Description page of Project Settings.

#include "RawFuryPlayerController.h"
#include "Kismet/GameplayStatics.h"

bool ARawFuryPlayerController::ShouldTakeControllerInput() const
{
    return !bIsMobile;
}

void ARawFuryPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    UpdateCurrentPlatform();

    if (bIsMobile && IsFirstPawn(aPawn))
    {
        OnPlayersConnected();
    }
}

void ARawFuryPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    if (bIsMobile && IsFirstPawn(GetPawn()))
    {
        OnPlayersInputTick();
    }
}

void ARawFuryPlayerController::UpdateCurrentPlatform()
{
    FString PlatformName = UGameplayStatics::GetPlatformName();
    bool bShouldUseMouseForTouch = UGameplayStatics::GetGameInstance(GetWorld())->GetGameViewportClient()->GetUseMouseForTouch();

    if (PlatformName == "Android" || PlatformName == "IOS" || bShouldUseMouseForTouch)
    {
        bIsMobile = true;
    }
    else
    {
        bIsMobile = false;
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
