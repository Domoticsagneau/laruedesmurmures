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
