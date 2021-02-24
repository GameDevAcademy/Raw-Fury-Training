// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RawFuryTrainingGameMode.generated.h"

class ARawFuryTrainingPawn;

UENUM(BlueprintType)
namespace ERawFuryGameState
{
    enum Type
    {
        Start,
        ChoseAbilities,
        Play,
        Finish
    };
}

UCLASS(MinimalAPI)
class ARawFuryTrainingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARawFuryTrainingGameMode();

public:
    bool IsPlayingMobile() const { return bIsMobile; }

// AGameModeBase interface
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

// Internal functionality
private:
    void SpawnPlayer(const FTransform& SpawnTransform, int32 PlayerIndex);

// Serialized variables
protected:
    /** The default spaceship class used by players. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RawFury)
    TSubclassOf<ARawFuryTrainingPawn> SpaceshipClass;

private:
    ERawFuryGameState::Type GameState = ERawFuryGameState::Start;
    bool bIsMobile = false;
};



