// Copyright Epic Games, Inc. All Rights Reserved.

#include "RawFuryTrainingPawn.h"

#include "RawFuryTraining.h"

#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"

namespace
{
    struct AxisBindings
    {
        AxisBindings(FName InForwardAxis, FName InRightAxis)
        {
            MoveForwardBinding = InForwardAxis;
            MoveRightBinding = InRightAxis;
        }

        FName MoveForwardBinding;
        FName MoveRightBinding;
    };

    TArray<AxisBindings> PlayerInputs =
    {
        AxisBindings("MoveForwardL", "MoveRightL"),
        AxisBindings("MoveForwardR", "MoveRightR")
    };
}

ARawFuryTrainingPawn::ARawFuryTrainingPawn()
{
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	// Replace the root with the mesh component created above.
	RootComponent = ShipMeshComponent;
}

void ARawFuryTrainingPawn::Tick(float DeltaSeconds)
{
    TickMovement(DeltaSeconds);
}

void ARawFuryTrainingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // set up gameplay key bindings
    for (const AxisBindings& PlayerInput : PlayerInputs)
    {
        PlayerInputComponent->BindAxis(PlayerInput.MoveForwardBinding);
        PlayerInputComponent->BindAxis(PlayerInput.MoveRightBinding);
    }
}

void ARawFuryTrainingPawn::TickMovement(float DeltaSeconds)
{
    // Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
    const FVector MoveDirection = GetInputByControllerId().GetClampedToMaxSize(1.0f);

    // Calculate  movement
    const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

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

FVector ARawFuryTrainingPawn::GetInputByControllerId() const
{
    return FVector::ZeroVector;

    int32 ControllerId = 0;
    
    FName ForwardAxis;
    FName RightAxis;

    if (ControllerId > PlayerInputs.Num())
    {
        UE_LOG(LogRawFuryTraining, Error, TEXT("Axis not implemented for controllerid %i"), ControllerId);
        return FVector::ZeroVector;
    }

    ForwardAxis = PlayerInputs[ControllerId].MoveForwardBinding;
    RightAxis = PlayerInputs[ControllerId].MoveRightBinding;

    UInputComponent* LocalInputComponent = nullptr;

    float ForwardValue = 0.0f;
    float RightValue = 0.0f;

    if (LocalInputComponent)
    {
        ForwardValue = LocalInputComponent->GetAxisKeyValue(ForwardAxis);
        RightValue = LocalInputComponent->GetAxisKeyValue(RightAxis);
    }
    else
    {
        ForwardValue = GetInputAxisValue(ForwardAxis);
        RightValue = GetInputAxisValue(RightAxis);
    }

    return FVector(ForwardValue, RightValue, 0.0f);
}
