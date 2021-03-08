// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RawFuryTrainingGameMode.generated.h"

class ARawFuryTrainingPawn;
class URawFuryBaseAbility;
class SRawFuryScoreWidget;

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

USTRUCT(BlueprintType)
struct FAsteroidSpawnInfo
{
    GENERATED_USTRUCT_BODY();

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int32 AsteroidsToSpawn = 100;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        TSubclassOf<AActor> AsteroidClassToSpawn;
};

UCLASS(BlueprintType, EditInlineNew)
class URawFuryWidgetInfo : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Custom Object")
    bool bShouldShow = true;
};

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

    UFUNCTION(BlueprintCallable)
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = RawFury)
    URawFuryWidgetInfo* RawFuryWidgetInfo;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RawFury)
    FAsteroidSpawnInfo AsteroidSpawnInfo;

private:
    ERawFuryGameState::Type GameState = ERawFuryGameState::None;

    TArray<ARawFuryTrainingPawn*> Players;
    TSharedPtr<SRawFuryScoreWidget> ScoreWidget;

    bool bIsMobile = false;
};



