// GameDev Academy 2021 - RawFury Training v1.0

#include "AsteroidComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RawFuryTrainingGameMode.h"

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

    AGameModeBase* CurrentGameMode = UGameplayStatics::GetGameMode(GetWorld());
    if (ARawFuryTrainingGameMode* RawFuryGameMode = Cast<ARawFuryTrainingGameMode>(CurrentGameMode))
    {
        RawFuryGameMode->OnSomethingHappened.AddDynamic(this, &UAsteroidComponent::OnSomethingHappendFunction);
    }

    StateFlags |= static_cast<uint8>(EAsteroidStateFlags::Spawned);

    USphereComponent* SphereCollider = GetOwner()->FindComponentByClass<USphereComponent>();
    SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &UAsteroidComponent::OnComponentOverlapBegin);
}

void UAsteroidComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    
    StateFlags &= ~static_cast<uint8>(EAsteroidStateFlags::Spawned);
}

void UAsteroidComponent::OnSomethingHappendFunction(bool info)
{
    UE_LOG(LogTemp, Warning, TEXT("UAsteroidComponent::OnSomethingHappendFunction"));
}

void UAsteroidComponent::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    /*GetOwner()->Destroy();*/
    AGameModeBase* CurrentGameMode = UGameplayStatics::GetGameMode(GetWorld());
    if (ARawFuryTrainingGameMode* RawFuryGameMode = Cast<ARawFuryTrainingGameMode>(CurrentGameMode))
    {
        RawFuryGameMode->ReturnAsteroid(GetOwner());
    }
}

// Called every frame
void UAsteroidComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const int UpdateEveryFrames = 10;

    if (FramesSinceLastUpdate % UpdateEveryFrames != 0) // 1, 2, ... 9
    {
        TotalDeltaTime += DeltaTime;
        return;
    }

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

    if (StateFlags & static_cast<uint8>(EAsteroidStateFlags::Spawned))
    {
        StateFlags |= static_cast<uint8>(EAsteroidStateFlags::ChangedDirection);
    }
}