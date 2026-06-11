#include "LevelSequenceController.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"

ALevelSequenceController
::ALevelSequenceController()
{
    PrimaryActorTick.bCanEverTick = false;

    CurrentPlayer = nullptr;
    CurrentActor = nullptr;
}

ULevelSequence*
ALevelSequenceController
::FindSequence(
    const FString& Name)
{
    for (const auto& Entry : Sequences)
    {
        if (Entry.SequenceName == Name)
        {
            return Entry.Sequence;
        }
    }

    return nullptr;
}

void ALevelSequenceController
::PlaySequence(
    const FString& SequenceName)
{
    ULevelSequence* Sequence =
        FindSequence(
            SequenceName);

    if (!Sequence)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("Sequence not found"));
        return;
    }
    FMovieSceneSequencePlaybackSettings Settings;

    CurrentPlayer =
        ULevelSequencePlayer
        ::CreateLevelSequencePlayer(
            GetWorld(),
            Sequence,
            Settings,
            CurrentActor);

    if (CurrentPlayer)
    {
        CurrentPlayer->Play();
    }
}

void ALevelSequenceController
::StopSequence()
{
    if (CurrentPlayer)
    {
        CurrentPlayer->Stop();
    }
}

