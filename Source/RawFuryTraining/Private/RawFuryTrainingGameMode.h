// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RawFuryTrainingGameMode.generated.h"

class ARawFuryTrainingPawn;
class URawFuryBaseAbility;

UENUM(BlueprintType)
namespace ERawFuryGameState
{
    enum Type
    {
        None,
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
    UFUNCTION(BlueprintCallable)
    void ChangeGameState(ERawFuryGameState::Type NewState);

    UFUNCTION(BlueprintImplementableEvent)
    void OnNewGameState(ERawFuryGameState::Type NewState);

    bool IsPlayingMobile() const;

// AGameModeBase interface
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

// Internal functionality
private:
    void SpawnPlayer(const FTransform& SpawnTransform, int32 PlayerIndex);
    void AssignRandomAbilities();

// Serialized variables
protected:
    /** The default spaceship class used by players. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RawFury)
    TSubclassOf<ARawFuryTrainingPawn> SpaceshipClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RawFury)
    TArray<TSubclassOf<URawFuryBaseAbility>> AllAbilities;

private:
    ERawFuryGameState::Type GameState = ERawFuryGameState::None;

    TArray<ARawFuryTrainingPawn*> Players;
    bool bIsMobile = false;
};



