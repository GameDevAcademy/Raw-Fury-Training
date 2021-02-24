// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "RawFuryTrainingPawn.generated.h"

class URawFuryBaseAbility;

UCLASS(Blueprintable)
class ARawFuryTrainingPawn : public APawn
{
	GENERATED_BODY()
public:
	ARawFuryTrainingPawn();

// Damaging
public:
    UFUNCTION(BlueprintCallable)
    void DealDamage(float Damage);

// Input
public:
    UFUNCTION(BlueprintCallable)
    void UpdateInput(float InX, float InY);

// Abilities
public:
    UFUNCTION(BlueprintCallable)
    void StartSpeedMultiplyer(float ExtraSpeed) { MoveSpeedMultiplyer = ExtraSpeed; }

    UFUNCTION(BlueprintCallable)
    void StopSpeedMultiplyer() { MoveSpeedMultiplyer = 1.0f; }

    UFUNCTION(BlueprintCallable)
    void StartInvulnerability() { bIsInvulnerable = true; }

    UFUNCTION(BlueprintCallable)
    void StopInvulnerability() { bIsInvulnerable = false; }

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void OnHealthChanged(float NewHealthPercentage);

// APawn interface
protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
// Internal functionality
private:
    void TickMovement(float DeltaSeconds);

// Serialized
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RawFury)
    TSubclassOf<URawFuryBaseAbility> AbilityTemplate;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = RawFury)
    URawFuryBaseAbility* CurrentAbility;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = RawFury)
    class UStaticMeshComponent* ShipMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RawFury)
    float MoveSpeed = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RawFury)
    float StartHealth = 100.0f;

// Internals
private:
    FVector ControllerInput = FVector::ZeroVector;

    float MoveSpeedMultiplyer = 1.0f;
    float Health = 100.0f;
    bool bIsInvulnerable = false;
};

