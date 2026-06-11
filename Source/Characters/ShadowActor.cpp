#include "ShadowActor.h"

AShadowActor::AShadowActor()
{
    PrimaryActorTick.bCanEverTick = true;

    bMoving = false;
}

void AShadowActor::Appear()
{
    SetActorHiddenInGame(false);

    SetActorEnableCollision(true);
}

void AShadowActor::Disappear()
{
    SetActorHiddenInGame(true);

    SetActorEnableCollision(false);
}

void AShadowActor::TeleportToPoint(
    FVector Location)
{
    SetActorLocation(
        Location);
}

void AShadowActor::MoveToward(
    FVector TargetLocation)
{
    MoveTarget =
        TargetLocation;

    bMoving = true;
}

void AShadowActor::Tick(
    float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bMoving)
    {
        return;
    }

    FVector Current =
        GetActorLocation();

    FVector Direction =
        (MoveTarget - Current)
        .GetSafeNormal();

    FVector NewLocation =
        Current +
        Direction * 120.f *
        DeltaTime;

    SetActorLocation(
        NewLocation);

    if (FVector::Dist(
        NewLocation,
        MoveTarget)
        < 50.f)
    {
        bMoving = false;
    }
}
