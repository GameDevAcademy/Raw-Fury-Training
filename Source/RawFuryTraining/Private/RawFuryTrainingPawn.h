// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "RawFuryTrainingPawn.generated.h"

class URawFuryBaseAbility;
class UParticleSystem;

USTRUCT(BlueprintType)
struct FDamageFeedback
{
    GENERATED_USTRUCT_BODY();

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float TriggerHealthPercentage = 0.5f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UParticleSystem* EmitterTemplate;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 MaterialIndex = -1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UMaterial* MaterialOverride;
};

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

    bool IsDead() const;

// Input
public:
    UFUNCTION(BlueprintCallable)
    void UpdateInput(float InX, float InY);

    UFUNCTION(BlueprintCallable)
    void TriggerAbility(int32 AbilityIndex);

    UFUNCTION(BlueprintCallable)
    float GetAbilityCooldown(int32 AbilityIndex) const;

    UFUNCTION(BlueprintCallable)
    void StartCalculatingPrimeNumbers(bool bRunAsync);

// Abilities implementation
public:
    UFUNCTION(BlueprintCallable)
    void AddAbility(TSubclassOf<URawFuryBaseAbility> NewAbilityTemplate, int32 NewIndex = 0);

    UFUNCTION(BlueprintCallable)
    UTexture2D* GetAbilityImage(int32 Index = 0);

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

    UFUNCTION(BlueprintImplementableEvent)
    void OnDamageFeedbackChanged(const FDamageFeedback& NewDamageFeedback);

    UFUNCTION()
    void OnActorOverlapTrigged(AActor* OverlappedActor, AActor* OtherActor);

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
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = RawFury)
    TArray<URawFuryBaseAbility*> CurrentAbilities;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = RawFury)
    TArray<FDamageFeedback> DamageFeedbacks;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = RawFury)
    class UStaticMeshComponent* ShipMeshComponent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RawFury)
    float MoveSpeed = 300.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RawFury)
    float AbilityOffset = 150.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RawFury)
    float StartHealth = 100.0f;

// Internals
private:
    FVector ControllerInput = FVector::ZeroVector;

    float Health = 100.0f;
    bool bIsInvulnerable = false;
    float MoveSpeedMultiplyer = 1.0f;
    int32 DamageFeedbackIndex = -1;

    int32 FramesSinceLastUpdate = 0;
};

