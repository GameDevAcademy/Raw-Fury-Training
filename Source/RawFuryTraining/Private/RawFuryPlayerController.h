// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RawFuryPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARawFuryPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	bool ShouldTakeControllerInput() const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayersConnected();

    UFUNCTION(BlueprintImplementableEvent)
	void OnPlayersInputTick();

private:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime);

private:
	void UpdateCurrentPlatform();
	bool IsFirstPawn(APawn* aPawn) const;
};
