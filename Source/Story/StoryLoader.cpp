#include "StoryLoader.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool FStoryLoader::LoadStory(
    const FString& FilePath,
    FStoryData& OutStory)
{
    FString JsonString;

    if (!FFileHelper::LoadFileToString(
        JsonString,
        *FilePath))
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("Impossible de lire %s"),
            *FilePath);

        return false;
    }

    return ParseStory(
        JsonString,
        OutStory);
}

bool FStoryLoader::ParseStory(
    const FString& JsonString,
    FStoryData& OutStory)
{
    TSharedPtr<FJsonObject> RootObject;

    TSharedRef<TJsonReader<>> Reader =
        TJsonReaderFactory<>::Create(
            JsonString);

    if (!FJsonSerializer::Deserialize(
        Reader,
        RootObject))
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("JSON invalide"));

        return false;
    }

    const TArray<TSharedPtr<FJsonValue>>* EventsArray;

    if (!RootObject->TryGetArrayField(
        TEXT("events"),
        EventsArray))
    {
        return false;
    }

    OutStory.Events.Empty();
    for (const auto& EventValue : *EventsArray)
    {
        const TSharedPtr<FJsonObject> EventObject =
            EventValue->AsObject();

        FStoryEvent Event;

        Event.Time =
            EventObject->GetNumberField(
                TEXT("time"));

        Event.Camera =
            EventObject->GetStringField(
                TEXT("camera"));

        Event.Action =
            EventObject->GetStringField(
                TEXT("action"));

        EventObject->TryGetStringField(
            TEXT("parameter"),
            Event.Parameter);

        OutStory.Events.Add(Event);
    }

    return true;
}
