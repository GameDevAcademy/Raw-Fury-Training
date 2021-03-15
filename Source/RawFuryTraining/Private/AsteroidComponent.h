// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AsteroidComponent.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EAsteroidStateFlags : uint8
{
    NoFlags             = 0,
    Spawned             = (1 << 0),
    ChangedDirection    = (1 << 1),
    Destroyed           = (1 << 2),
    Pooled              = (1 << 3),
};
ENUM_CLASS_FLAGS(EAsteroidStateFlags);

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

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintPure)
    float GetPercentageLeft() const;

    UFUNCTION(BlueprintCallable)
    void StartAsteroid();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChangeInterval = 5.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TimePassed = 0.0f;

    UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "EAsteroidStateFlags"))
    uint8 StateFlags;
};