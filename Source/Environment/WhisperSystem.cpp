#include "WhisperSystem.h"

#include "Kismet/GameplayStatics.h"

void AWhisperSystem::PlayWhisper(FVector Location)
{
    if (WhisperSounds.Num() == 0)
    {
        return;
    }

    UGameplayStatics
    ::PlaySoundAtLocation(
        this,
        WhisperSounds[0],
        Location);
}

void AWhisperSystem::PlayRandomWhisper(
    FVector AroundLocation,
    float Radius)
{
    if (WhisperSounds.Num() == 0)
    {
        return;
    }

    FVector Offset;

    Offset.X =
        FMath::RandRange(
            -Radius,
             Radius);

    Offset.Y =
        FMath::RandRange(
            -Radius,
             Radius);

    Offset.Z = 0.f;

    int32 Index =
        FMath::RandRange(
            0,
            WhisperSounds.Num()-1);

    UGameplayStatics
    ::PlaySoundAtLocation(
        this,
        WhisperSounds[Index],
        AroundLocation + Offset);
}


