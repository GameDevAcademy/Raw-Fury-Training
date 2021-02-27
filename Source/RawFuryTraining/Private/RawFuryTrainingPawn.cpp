// Copyright Epic Games, Inc. All Rights Reserved.

#include "RawFuryTrainingPawn.h"

#include "RawFuryTraining.h"
#include "RawFuryPlayerController.h"
#include "RawFuryBaseAbility.h"

#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"

namespace
{
    const FName MoveForwardBinding("MoveForward");
    const FName MoveRightBinding("MoveRight");

    const FName TriggerAbility0Binding("TriggerAbility0");
    const FName TriggerAbility1Binding("TriggerAbility1");
}

ARawFuryTrainingPawn::ARawFuryTrainingPawn()
{
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	// Replace the root with the mesh component created above.
	RootComponent = ShipMeshComponent;
}

void ARawFuryTrainingPawn::UpdateInput(float InX, float InY)
{
    ControllerInput = FVector(InY, InX, 0.0f);
}

void ARawFuryTrainingPawn::TriggerAbility(int32 AbilityIndex)
{
    if (AbilityIndex >= CurrentAbilities.Num())
    {
        UE_LOG(LogRawFuryTraining, Warning, TEXT("Triggering an ability with an index above the current ones."));
        return;
    }

    if (URawFuryBaseAbility* SelectedAbility = CurrentAbilities[AbilityIndex])
    {
        SelectedAbility->TryTrigger(GetActorTransform(), FVector::ForwardVector * AbilityOffset);
    }
}

float ARawFuryTrainingPawn::GetAbilityCooldown(int32 AbilityIndex) const
{
    if (AbilityIndex >= CurrentAbilities.Num())
    {
        return -1.0f;
    }

    if (URawFuryBaseAbility* SelectedAbility = CurrentAbilities[AbilityIndex])
    {
        return SelectedAbility->GetCoolDownPercentage();
    }

    return -1.0f;
}

void ARawFuryTrainingPawn::AddAbility(TSubclassOf<URawFuryBaseAbility> NewAbilityTemplate, int32 NewIndex)
{
    if (NewAbilityTemplate)
    {
        URawFuryBaseAbility* NewAbility = NewObject<URawFuryBaseAbility>(this, NewAbilityTemplate);

        if (NewAbility)
        {
            NewAbility->InitAbility(GetWorld(), this);

            if (NewIndex < CurrentAbilities.Num())
            {
                CurrentAbilities.Insert(NewAbility, NewIndex);
            }
            else
            {
                CurrentAbilities.Emplace(NewAbility);
            }

        }
    }
}

void ARawFuryTrainingPawn::DealDamage(float Damage)
{
    if (bIsInvulnerable)
    {
        return;
    }

    Health -= Damage;

    float CurrentPercentage = Health / StartHealth;
    OnHealthChanged(CurrentPercentage);

    for (int32 i = 0; i < DamageFeedbacks.Num(); i++)
    {
        if (DamageFeedbacks[i].TriggerHealthPercentage > CurrentPercentage && i > DamageFeedbackIndex)
        {
            OnDamageFeedbackChanged(DamageFeedbacks[i]);
            DamageFeedbackIndex = i;
        }
    }
}

bool ARawFuryTrainingPawn::IsDead() const
{
    return Health <= 0.0f;
}

void ARawFuryTrainingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    // set up gameplay key bindings
    PlayerInputComponent->BindAxis(MoveForwardBinding);
    PlayerInputComponent->BindAxis(MoveRightBinding);

    DECLARE_DELEGATE_OneParam(FOnAbilityInputTrigger, int32);

    PlayerInputComponent->BindAction<FOnAbilityInputTrigger>(TriggerAbility0Binding, EInputEvent::IE_Pressed, this, &ARawFuryTrainingPawn::TriggerAbility, 0);
    PlayerInputComponent->BindAction<FOnAbilityInputTrigger>(TriggerAbility1Binding, EInputEvent::IE_Pressed, this, &ARawFuryTrainingPawn::TriggerAbility, 1);
}

void ARawFuryTrainingPawn::BeginPlay()
{
    Super::BeginPlay();

    Health = StartHealth;
    OnHealthChanged(Health / StartHealth);

    DamageFeedbacks.Sort([](const FDamageFeedback& A, const FDamageFeedback& B) 
        {
            return A.TriggerHealthPercentage > B.TriggerHealthPercentage;
        });
}

void ARawFuryTrainingPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    for (const auto& AbilityPtr : CurrentAbilities)
    {
        if (AbilityPtr)
        {
            AbilityPtr->StopAbility();
        }
    }

    CurrentAbilities.Empty();
}

void ARawFuryTrainingPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (ARawFuryPlayerController* PlayerController = GetController<ARawFuryPlayerController>())
    {
        if (PlayerController->ShouldTakeControllerInput())
        {
            const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
            const float RightValue = GetInputAxisValue(MoveRightBinding);

            UpdateInput(RightValue, ForwardValue);
        }
    }

    TickMovement(DeltaSeconds);
}

void ARawFuryTrainingPawn::TickMovement(float DeltaSeconds)
{
    // Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
    const FVector MoveDirection = ControllerInput.GetClampedToMaxSize(1.0f);

    // Calculate  movement
    const FVector Movement = MoveDirection * MoveSpeedMultiplyer * MoveSpeed * DeltaSeconds;

    // If non-zero size, move this actor
    if (Movement.SizeSquared() > 0.0f)
    {
        const FRotator NewRotation = Movement.Rotation();
        FHitResult Hit(1.f);
        RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

        if (Hit.IsValidBlockingHit())
        {
            const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
            const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
            RootComponent->MoveComponent(Deflection, NewRotation, true);
        }
    }
}
