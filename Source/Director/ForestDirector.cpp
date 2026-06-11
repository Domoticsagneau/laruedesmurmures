#include "ForestDirector.h"
#include "StoryLoader.h"
#include "Misc/Paths.h"
#include "LeoCharacter.h"
#include "ShadowActor.h"

AForestDirector::AForestDirector()
{
    PrimaryActorTick.bCanEverTick = true;

    CurrentTime = 0.f;
    CurrentEventIndex = 0;
}

void AForestDirector::BeginPlay()
{
    Super::BeginPlay();

    LoadStory();
}

void AForestDirector::LoadStory()
{
    FString JsonPath =
        FPaths::ProjectContentDir() +
        TEXT("Story/story.json");

    if (!FStoryLoader::LoadStory(
        JsonPath,
        Story))
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("Story loading failed"));

        return;
    }

    Story.Events.Sort(
        [](const FStoryEvent& A,
           const FStoryEvent& B)
        {
            return A.Time < B.Time;
        });

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Loaded %d events"),
        Story.Events.Num());
}

void AForestDirector::Tick(
    float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentTime += DeltaTime;
    while
    (
        Story.Events.IsValidIndex(
            CurrentEventIndex)
        &&
        Story.Events[
            CurrentEventIndex].Time
        <= CurrentTime
    )
    {
        ExecuteEvent(
            Story.Events[
                CurrentEventIndex]);

        CurrentEventIndex++;
    }
}
void AForestDirector::ExecuteEvent(
    const FStoryEvent& Event)
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Action : %s"),
        *Event.Action);
    if (Event.Action == "intro")
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("INTRO"));
    }
    else if (Event.Action == "walk") {
        if (Leo)
        {
            Leo->WalkForward();
        }
    }

    else if (Event.Action == "run") {
        if (Leo)
        {
            Leo->RunForward();
        }
    }
    else if (Event.Action == "stop") {
        Leo->StopMovement();
    }
    else if (Event.Action == "look_behind") {
        Leo->LookBehind();
    }        
    else if (Event.Action == "shadow_appear") {
        if (Shadow)
        {
            Shadow->Appear();
        }
    }
    else if (Event.Action == "shadow_disappear") {
        if (Shadow)
        {
            Shadow->Disappear();
        }
    }

    else if (Event.Action == "switch_camera") {
        if (CameraManager)
        {
            //int32 CameraIndex =
            //    FCString::Atoi(
            //        *Event.Parameter);
            CameraManager->BlendToCamera(
            Event.Parameter,
            1.5f);
            //CameraManager
            //    ->SwitchCamera(
            //        CameraIndex);
        }
    }

    else if (Event.Action == "mirror_reveal") {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Mirror reveal"));
    }
    else if (Event.Action == "sunset") {
        DayNight->StartSunset();
    }
    else if (Event.Action == "night") {
        DayNight->StartNight();
    }
    else if (Event.Action == "whisper") {
        Whisper->PlayRandomWhisper(Leo->GetActorLocation(),600.f);
    }
}

void AForestDirector::HandleTrigger(
    FString TriggerID)
{
    if (TriggerID == "ForestEntrance")
    {
        Shadow->Appear();

        Whisper->PlayRandomWhisper(
            Leo->GetActorLocation(),
            400.f);
    }

    else if (
        TriggerID == "WarningPanel")
    {
        CameraManager
        ->BlendToCamera(
            "Cam04",
            1.5f);
    }

    else if (
        TriggerID == "MirrorZone")
    {
        ExecuteMirrorReveal();
    }
}
