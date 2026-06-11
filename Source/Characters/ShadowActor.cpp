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
