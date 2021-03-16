// GameDev Academy 2021 - RawFury Training v1.0

#include "RawFuryTrainingGameMode.h"

#include "RawFuryTraining.h"
#include "RawFuryTrainingPawn.h"
#include "RawFuryScoreWidget.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "RawFuryTraining"

class EmptyClass
{
    int32 A;
};

class FirstDerivedClass : EmptyClass
{
    int32 B;
};

class SecondDerivedClass : FirstDerivedClass
{
    bool D;
};

class PowerPointExampleClass
{
	int16 A;
	int16 B;
	uint8 C;
};

class MorePropertiesGameMode : ARawFuryTrainingGameMode
{
public:
	int32 A;
	float B;
	int32 C;
};

void ARawFuryTrainingGameMode::LogClassInfo()
{
	size_t PowerPointExampleClassSize = sizeof PowerPointExampleClass;
	UE_LOG(LogTemp, Warning, TEXT("PowerPointExampleClass - %llu bytes"), PowerPointExampleClassSize);

	size_t EmptyClassSize = sizeof EmptyClass;
    UE_LOG(LogTemp, Warning, TEXT("EmptyClass - %llu bytes"), EmptyClassSize);

	size_t FirstDerivedClassSize = sizeof FirstDerivedClass;
    UE_LOG(LogTemp, Warning, TEXT("FirstDerivedClass - %llu bytes"), FirstDerivedClassSize);

	size_t SecondDerivedClassSize = sizeof SecondDerivedClass;
    UE_LOG(LogTemp, Warning, TEXT("SecondDerivedClass - %llu bytes"), SecondDerivedClassSize);

    size_t ARawFuryTrainingGameModeSize = sizeof ARawFuryTrainingGameMode;
    UE_LOG(LogTemp, Warning, TEXT("ARawFuryTrainingGameMode - %llu bytes"), ARawFuryTrainingGameModeSize);

    size_t MorePropertiesGameModeSize = sizeof MorePropertiesGameMode;
    UE_LOG(LogTemp, Warning, TEXT("MorePropertiesGameMode - %llu bytes"), MorePropertiesGameModeSize);
}

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

	switch (GameState)
	{
	case ERawFuryGameState::None:
		ScoreWidget->SetWidgetText(LOCTEXT("None", "None"));
		break;
	case ERawFuryGameState::Start:
		ScoreWidget->SetWidgetText(LOCTEXT("Prepare", "Prepare!"));
		break;
	case ERawFuryGameState::ChoseAbilities:
        ScoreWidget->SetWidgetText(LOCTEXT("ChoseYourAbilities", "Chose your abilities!"));
		break;
	case ERawFuryGameState::Play:
        ScoreWidget->SetWidgetText(LOCTEXT("KillYourOpponent", "Kill your opponent!"));
		break;
	case ERawFuryGameState::Finish:
        ScoreWidget->SetWidgetText(LOCTEXT("GameOver", "Game Over!"));
		break;

	}
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

    GEngine->GameViewport->AddViewportWidgetContent(
        SAssignNew(ScoreWidget, SRawFuryScoreWidget), 100
    );

	if (!IsPlayingMobile())
	{
        AssignRandomAbilities();
	}

	ChangeGameState(ERawFuryGameState::Start);

	for (int32 i = 0; i < AsteroidSpawnInfo.AsteroidsToSpawn; i++)
	{
        float RandomX = FMath::FRandRange(-1000.0f, 1000.0f);
        float RandomY = FMath::FRandRange(-1000.0f, 1000.0f);

		FVector SpawnLocation = FVector(RandomX, RandomY, 0.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		UWorld* CurrentWorld = GetWorld();
		AActor* AsteroidActor = CurrentWorld->SpawnActor<AActor>(AsteroidSpawnInfo.AsteroidClassToSpawn, SpawnLocation, SpawnRotation);
	}

	LogClassInfo();
}

void ARawFuryTrainingGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    OnSomethingHappened.Broadcast(true);

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
			for (const auto& Player : Players)
			{
				if (Player->IsDead())
				{
					ChangeGameState(ERawFuryGameState::Finish);
				}
			}

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

#undef LOCTEXT_NAMESPACE