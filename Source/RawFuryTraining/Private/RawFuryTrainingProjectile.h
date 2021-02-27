// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RawFuryTrainingProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config=Game)
class ARawFuryTrainingProjectile : public AActor
{
	GENERATED_BODY()

public:
	ARawFuryTrainingProjectile();

protected:
    UFUNCTION()
    void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RawFury)
	float ProjectileDamage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RawFury)
    FVector ParticlesSpawnOffset = FVector(0.0f, 0.0f, 10.0f);
};

