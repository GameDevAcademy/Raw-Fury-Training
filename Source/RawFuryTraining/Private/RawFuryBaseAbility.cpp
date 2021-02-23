// Fill out your copyright notice in the Description page of Project Settings.


#include "RawFuryBaseAbility.h"

#include "Kismet/GameplayStatics.h"

void URawFuryBaseAbility::InitAbility(UWorld* InOwnerWorld, ARawFuryTrainingPawn* InPawn)
{
    PlayerPawn = InPawn;
    OwnerWorld = InOwnerWorld;
}

void URawFuryBaseAbility::StopAbility()
{
    OwnerWorld = nullptr;
    PlayerPawn = nullptr;
}

bool URawFuryBaseAbility::TryTrigger(const FTransform& CurrentTransform, FVector TargetPosition)
{
    if (!IsOnCoolDown())
    {
        OnAbilityTriggered(CurrentTransform, TargetPosition);

        if (EffectDuration > 0.0f)
        {
            bIsEffectActive = true;

            FTimerManager& TimeManager = OwnerWorld->GetTimerManager();
            TimeManager.SetTimer(EffectDurationHandle, this, &URawFuryBaseAbility::TryFinish, EffectDuration, false);
        }
        else
        {
            TryFinish();
        }

        return true;
    }

    return false;
}

void URawFuryBaseAbility::TryFinish()
{
    if (!bIsEffectActive)
    {
        return;
    }

    bIsEffectActive = false;

    LastTriggerTime = UGameplayStatics::GetTimeSeconds(GetWorld()) + CoolDownDuration;

    OnAbilityDelepted();
}

bool URawFuryBaseAbility::IsOnCoolDown() const
{
    return bIsEffectActive || (UGameplayStatics::GetTimeSeconds(GetWorld()) < LastTriggerTime);
}
