// Copyright Epic Games, Inc. All Rights Reserved.

#include "RawFuryTrainingGameMode.h"

#include "RawFuryTraining.h"
#include "RawFuryTrainingPawn.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

ARawFuryTrainingGameMode::ARawFuryTrainingGameMode()
{
	// set default pawn class to our character class
	SpaceshipClass = ARawFuryTrainingPawn::StaticClass();
}

void ARawFuryTrainingGameMode::BeginPlay()
{
	Super::BeginPlay();
	
    TArray<AActor*> SpawnLocations;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnLocations);

	for (int32 SpawnIndex = 0; SpawnIndex < SpawnLocations.Num(); SpawnIndex++)
	{
		const FTransform& SpawnTransform = SpawnLocations[SpawnIndex]->GetTransform();
		SpawnPlayer(SpawnTransform, SpawnIndex);
	}
}

void ARawFuryTrainingGameMode::SpawnPlayer(const FTransform& SpawnTransform, int32 PlayerIndex)
{
	if (SpaceshipClass == nullptr)
	{
		UE_LOG(LogRawFuryTraining, Error, TEXT("Missing Spaceship class on gamemode!"));
		return;
	}

	// Create a controller if needed.
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex);
	if (!PlayerController)
	{
		PlayerController = UGameplayStatics::CreatePlayer(GetWorld(), PlayerIndex, true);
	}

	// Create actor and connect control.
	ARawFuryTrainingPawn* SpaceShipActor = GetWorld()->SpawnActor<ARawFuryTrainingPawn>(SpaceshipClass, SpawnTransform);
	PlayerController->Possess(SpaceShipActor);
}

