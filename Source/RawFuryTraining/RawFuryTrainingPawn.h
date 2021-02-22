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

// Components
protected:
    UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ShipMeshComponent;

};

