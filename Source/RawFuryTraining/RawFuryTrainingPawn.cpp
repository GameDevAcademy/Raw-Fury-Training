// Copyright Epic Games, Inc. All Rights Reserved.

#include "RawFuryTrainingPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"

ARawFuryTrainingPawn::ARawFuryTrainingPawn()
{
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	// Replace the root with the mesh component created above.
	RootComponent = ShipMeshComponent;
}
