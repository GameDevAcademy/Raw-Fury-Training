// GameDev Academy 2021 - RawFury Training v1.0


#include "AsteroidComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values for this component's properties
UAsteroidComponent::UAsteroidComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UAsteroidComponent::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("My asteroid is alive."));
}


// Called every frame
void UAsteroidComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    SCOPED_NAMED_EVENT_TEXT("UAsteroidComponent::TickComponent", FColor::Orange);

    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TimePassed += DeltaTime;

    if (TimePassed > ChangeInterval)
    {
        StartAsteroid();

        TimePassed = 0.0f;
    }
}

void UAsteroidComponent::StartAsteroid()
{
    SCOPED_NAMED_EVENT_TEXT("UAsteroidComponent::StartAsteroid", FColor::Purple);

    UE_LOG(LogTemp, Warning, TEXT("My asteroid is started."));

    FPlatformProcess::Sleep(0.5f);

    float RandomX = FMath::FRandRange(-100.0f, 100.0f);
    float RandomY = FMath::FRandRange(-100.0f, 100.0f);

    UProjectileMovementComponent* Projectile = GetOwner()->FindComponentByClass<UProjectileMovementComponent>();
    Projectile->Velocity = FVector(RandomX, RandomY, 0);
}