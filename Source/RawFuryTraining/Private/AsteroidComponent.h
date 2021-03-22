// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AsteroidComponent.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EAsteroidFlags : uint8
{
    WasAsteroidSpawned,
    WasAsteroidTicked,
    WasAsteroidDestroyed,
};
ENUM_CLASS_FLAGS(EAsteroidFlags);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UAsteroidComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAsteroidComponent();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION()
    void OnSomethingHappendFunction(bool info);

    UFUNCTION()
    void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintPure)
    float GetPercentageLeft() const;

    UFUNCTION(BlueprintPure)
    float GetTimeLeft() const;

    UFUNCTION(BlueprintCallable)
    void StartAsteroid();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChangeInterval = 5.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TimePassed = 0.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Bitmask, BitmaskEnum = "EAsteroidFlags"))
    uint8 AsteroidFlags;    
};