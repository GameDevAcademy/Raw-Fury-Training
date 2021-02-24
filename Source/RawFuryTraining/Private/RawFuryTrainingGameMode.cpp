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

	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
}

void ARawFuryTrainingGameMode::ChangeGameState(ERawFuryGameState::Type NewState)
{
	GameState = NewState;

	OnNewGameState(GameState);
}

bool ARawFuryTrainingGameMode::IsPlayingMobile() const
{
    FString PlatformName = UGameplayStatics::GetPlatformName();
    bool bShouldUseMouseForTouch = UGameplayStatics::GetGameInstance(GetWorld())->GetGameViewportClient()->GetUseMouseForTouch();

    if (PlatformName == "Android" || PlatformName == "IOS" || bShouldUseMouseForTouch)
    {
        return true;
    }
    else
    {
        return false;
    }
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

	GameState = ERawFuryGameState::Start;
}

void ARawFuryTrainingGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (GameState)
	{
		case ERawFuryGameState::None:
		{

			break;
		}
		case ERawFuryGameState::Start:
		{
			if (IsPlayingMobile())
			{
				ChangeGameState(ERawFuryGameState::ChoseAbilities);
			}
			else
			{
				AssignRandomAbilities();

				ChangeGameState(ERawFuryGameState::Play);
			}

			break;
		}
		case ERawFuryGameState::ChoseAbilities:
		{

			break;
		}
		case ERawFuryGameState::Play:
		{

			break;
		}
		case ERawFuryGameState::Finish:
		{

			break;
		}
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

	Players.Add(SpaceShipActor);
}

void ARawFuryTrainingGameMode::AssignRandomAbilities()
{
	int32 CurrentPlayerIndex = 0;

	while (AllAbilities.Num() > 0)
	{
		int32 RandomAbilityIndex = FMath::RandRange(0, AllAbilities.Num() - 1);

		Players[CurrentPlayerIndex]->AddAbility(AllAbilities[RandomAbilityIndex]);
		AllAbilities.RemoveAt(RandomAbilityIndex);

		CurrentPlayerIndex = (CurrentPlayerIndex + 1) % Players.Num();
	}
}