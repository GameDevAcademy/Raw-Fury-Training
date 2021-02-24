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
        LastTriggerTime = UGameplayStatics::GetTimeSeconds(GetWorld());

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

    OnAbilityDelepted();
}

bool URawFuryBaseAbility::IsOnCoolDown() const
{
    return GetCoolDownPercentage() < 1.0f;
}

float URawFuryBaseAbility::GetCoolDownPercentage() const
{
    // Ability was never triggered, it means it's ready
    if (LastTriggerTime < 0.0f)
    {
        return 1.0f;
    }

    // Ability is currently active, it didn't start cooldown yet
    if (bIsEffectActive)
    {
        return 0.0f;
    }

    float TimeNow = UGameplayStatics::GetTimeSeconds(GetWorld());

    float ElapsedTime = TimeNow - LastTriggerTime;
    return ElapsedTime / CoolDownDuration;
}
