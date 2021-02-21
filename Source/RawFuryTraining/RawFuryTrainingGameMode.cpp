// Copyright Epic Games, Inc. All Rights Reserved.

#include "RawFuryTrainingGameMode.h"
#include "RawFuryTrainingPawn.h"

ARawFuryTrainingGameMode::ARawFuryTrainingGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ARawFuryTrainingPawn::StaticClass();
}

