// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "RawFuryTrainingPawn.generated.h"

UCLASS(Blueprintable)
class ARawFuryTrainingPawn : public APawn
{
	GENERATED_BODY()
public:
	ARawFuryTrainingPawn();

public:
    void SetControllerIndex(int32 InIndex) { ControllerIndex = InIndex; }

    UFUNCTION(BlueprintCallable)
    void UpdateInput(int32 InControllerIndex, float InX, float InY);

// APawn interface
protected:
    virtual void Tick(float DeltaSeconds) override;
    
// Internal functionality
private:
    void TickMovement(float DeltaSeconds);

// Components
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = RawFury)
    class UStaticMeshComponent* ShipMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RawFury)
    float MoveSpeed = 300.0f;

private:
    int32 ControllerIndex = -1;
    FVector ControllerInput;
};

