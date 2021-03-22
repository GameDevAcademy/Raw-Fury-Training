// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AsteroidComponent.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EAsteroidStateFlags : uint8
{
    Spawned             = 0,
    ChangedDirection    = (1 << 0),
    Destroyed           = (1 << 1),
    Pooled              = (1 << 2),
};
ENUM_CLASS_FLAGS(EAsteroidStateFlags);

UENUM(BlueprintType, meta = (Bitflags))
enum class EAsteroidFlags : uint8
{
    NoFlags = 0,
    WasAsteroidSpawned = 1,
    WasAsteroidHit = 2,
    IsAsteroidInPool = 4,
    IsAsteroidRed = 8,
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

    // 4 booleans => lose 28 bits.

    uint8 Flags; 

    /// uint8 (3) - 00000011
    /// 0  = 00000000 = 0   = 1 << 0
    /// 1  = 00000001 = 2^0 = 1 << 1
    /// 2  = 00000010 = 2^1 = 1 << 2
    /// 4  = 00000100 = 2^2 = 1 << 3
    /// 8  = 00001000 = 2^3 = 1 << 4
    /// 16 = 00010000 = 2^4 = 1 << 5
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Bitmask, BitmaskEnum = "EAsteroidFlags"))
    uint8 AsteroidFlags;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Bitmask, BitmaskEnum = "EAsteroidStateFlags"))
    uint8 StateFlags;

    uint8 FramesSinceLastUpdate = 0;
    float TotalDeltaTime = 0;
    uint8 AsteroidNumber = 0;
};