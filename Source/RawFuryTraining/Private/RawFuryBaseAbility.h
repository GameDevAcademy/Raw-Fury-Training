// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RawFuryBaseAbility.generated.h"

class UWorld;
class ARawFuryTrainingPawn;

/**
 * 
 */
UCLASS(Blueprintable)
class URawFuryBaseAbility : public UObject
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintImplementableEvent)
	void OnAbilityTriggered(const FTransform& CurrentTransform, FVector TargetPosition);

    UFUNCTION(BlueprintImplementableEvent)
	void OnAbilityDelepted();

	UFUNCTION(BlueprintCallable)
	bool TryTrigger(const FTransform& CurrentTransform, FVector TargetPosition);

	void TryFinish();

public:
	void InitAbility(UWorld* InOwnerWorld, ARawFuryTrainingPawn* InPawn);
	void StopAbility();

	bool IsOnCoolDown() const;
	float GetCoolDownPercentage() const;

private:
	virtual class UWorld* GetWorld() const { return OwnerWorld; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RawFury)
	float CoolDownDuration = 5.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RawFury)
	float EffectDuration = -1.0f;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = RawFury)
	ARawFuryTrainingPawn* PlayerPawn = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = RawFury)
	UTexture2D* Texture = nullptr;

private:
	float LastTriggerTime = -1.0f;

	bool bIsEffectActive = false;

	UWorld* OwnerWorld = nullptr;

	FTimerHandle EffectDurationHandle;
};
