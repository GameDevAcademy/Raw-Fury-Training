// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AsteroidComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UAsteroidComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAsteroidComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void StartAsteroid();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChangeInterval = 5.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TimePassed = 0.0f;
};