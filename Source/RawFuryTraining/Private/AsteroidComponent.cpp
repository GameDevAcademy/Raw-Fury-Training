// GameDev Academy 2021 - RawFury Training v1.0

#include "AsteroidComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RawFuryTrainingGameMode.h"

#define TEST_BIT(Bitmask, Bit) 	(((Bitmask) & (1 << static_cast<uint32>(Bit))) > 0)
#define SET_BIT(Bitmask, Bit) 	(Bitmask |= 1 << static_cast<uint32>(Bit))
#define CLEAR_BIT(Bitmask, Bit) 	(Bitmask &= ~(1 << static_cast<uint32>(Bit)))

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

    SET_BIT(AsteroidFlags, EAsteroidFlags::WasAsteroidSpawned);

    USphereComponent* SphereCollider = GetOwner()->FindComponentByClass<USphereComponent>();
    SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &UAsteroidComponent::OnComponentOverlapBegin);
}

void UAsteroidComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    SET_BIT(AsteroidFlags, EAsteroidFlags::WasAsteroidDestroyed);
}

void UAsteroidComponent::OnSomethingHappendFunction(bool info)
{
    UE_LOG(LogTemp, Warning, TEXT("UAsteroidComponent::OnSomethingHappendFunction"));
}

void UAsteroidComponent::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //GetOwner()->Destroy();
}

// Called every frame
void UAsteroidComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    SCOPED_NAMED_EVENT_TEXT("UAsteroidComponent::TickComponent", FColor::Orange);

    TimePassed += DeltaTime;

    if (TimePassed > ChangeInterval)
    {
        StartAsteroid();

        TimePassed = 0.0f;
    }
}

float UAsteroidComponent::GetPercentageLeft() const
{
    return TimePassed / ChangeInterval;
}

float UAsteroidComponent::GetTimeLeft() const
{
    SCOPED_NAMED_EVENT_TEXT("UAsteroidComponent::GetTimeLeft", FColor::Purple);
    
    return ChangeInterval - TimePassed;
}

void UAsteroidComponent::StartAsteroid()
{
    SCOPED_NAMED_EVENT_TEXT("UAsteroidComponent::StartAsteroid", FColor::Purple);
    
    UE_LOG(LogTemp, Warning, TEXT("My asteroid is started."));

    float RandomX = FMath::FRandRange(-100.0f, 100.0f);
    float RandomY = FMath::FRandRange(-100.0f, 100.0f);

    UProjectileMovementComponent* Projectile = GetOwner()->FindComponentByClass<UProjectileMovementComponent>();
    Projectile->Velocity = FVector(RandomX, RandomY, 0);
    
    if (!TEST_BIT(AsteroidFlags, EAsteroidFlags::WasAsteroidTicked))
    {
        SET_BIT(AsteroidFlags, EAsteroidFlags::WasAsteroidTicked);
    }
}