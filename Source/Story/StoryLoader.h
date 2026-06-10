#pragma once

#include "CoreMinimal.h"
#include "StoryTypes.h"

class LARUEDESMURMURES_API FStoryLoader
{
public:

    static bool LoadStory(
        const FString& FilePath,
        FStoryData& OutStory);

private:

    static bool ParseStory(
        const FString& JsonString,
        FStoryData& OutStory);
};
