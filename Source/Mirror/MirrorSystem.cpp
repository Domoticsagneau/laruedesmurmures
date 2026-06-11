#include "MirrorSystem.h"

#include "TimerManager.h"
#include "Engine/World.h"

AMirrorSystem::AMirrorSystem()
{
    PrimaryActorTick.bCanEverTick = false;

    bRevealStarted = false;
}

void AMirrorSystem::BeginPlay()
{
    Super::BeginPlay();
}

void AMirrorSystem::StartMirrorReveal()
{
    if (bRevealStarted)
    {
        return;
    }

    bRevealStarted = true;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Mirror reveal started"));
    if (Shadow)
    {
        Shadow->Appear();
    }

    if (CameraManager)
    {
        CameraManager->BlendToCamera(
            TEXT("Cam05"),
            2.0f);
    }

    GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {BreakMirror();});
}

void AMirrorSystem::BreakMirror()
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Mirror broken"));

    if (Shadow)
    {
        Shadow->Disappear();
    }
    EndSequence();
}

