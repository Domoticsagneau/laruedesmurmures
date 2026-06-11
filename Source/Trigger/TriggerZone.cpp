#include "TriggerZone.h"

#include "Components/BoxComponent.h"
#include "LeoCharacter.h"

ATriggerZone::ATriggerZone()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox =
        CreateDefaultSubobject<UBoxComponent>(
            TEXT("TriggerBox"));

    RootComponent = TriggerBox;

    bAlreadyTriggered = false;
}

void ATriggerZone::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox
    ->OnComponentBeginOverlap
    .AddDynamic(
        this,
        &ATriggerZone::OnBeginOverlap);
}

void ATriggerZone::OnBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (bTriggerOnlyOnce &&
        bAlreadyTriggered)
    {
        return;
    }

    if (!Cast<ALeoCharacter>(
        OtherActor))
    {
        return;
    }

    bAlreadyTriggered = true;

    OnTriggerActivated.Broadcast(
        TriggerID);

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Trigger %s activated"),
        *TriggerID);
}

