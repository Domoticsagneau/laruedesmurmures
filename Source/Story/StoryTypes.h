#pragma once

#include "CoreMinimal.h"
#include "StoryTypes.generated.h"

USTRUCT(BlueprintType)
struct FStoryEvent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    float Time = 0.f;

    UPROPERTY(EditAnywhere)
    FString Camera;

    UPROPERTY(EditAnywhere)
    FString Action;

    UPROPERTY(EditAnywhere)
    FString Parameter;
};

USTRUCT(BlueprintType)
struct FStoryData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TArray<FStoryEvent> Events;
};
