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

// APawn inteface
protected:
    virtual void Tick(float DeltaSeconds) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Internal functionality
private:
    void TickMovement(float DeltaSeconds);
    FVector GetInputByControllerId() const;

// Components
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = RawFury)
    class UStaticMeshComponent* ShipMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RawFury)
    float MoveSpeed = 300.0f;

};

