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

void ARawFuryTrainingPawn::DealDamage(float Damage)
{
    if (bIsInvulnerable)
    {
        return;
    }

    Health -= Damage;

    OnHealthChanged(Health / StartHealth);
}

void ARawFuryTrainingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    // set up gameplay key bindings
    PlayerInputComponent->BindAxis(MoveForwardBinding);
    PlayerInputComponent->BindAxis(MoveRightBinding);
}

void ARawFuryTrainingPawn::BeginPlay()
{
    Super::BeginPlay();

    if (AbilityTemplate)
    {
        CurrentAbility = NewObject<URawFuryBaseAbility>(this, AbilityTemplate);

        if (CurrentAbility)
        {
            CurrentAbility->InitAbility(GetWorld(), this);
        }
    }

    Health = StartHealth;
    OnHealthChanged(Health / StartHealth);
}

void ARawFuryTrainingPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (CurrentAbility)
    {
        CurrentAbility->StopAbility();
    }

    CurrentAbility = nullptr;
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
