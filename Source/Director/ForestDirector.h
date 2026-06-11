#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "StoryTypes.h"

#include "ForestDirector.generated.h"

class ACameraManager;
class AShadowActor;
class ALeoCharacter;

UCLASS()
class LARUEDESMURMURES_API AForestDirector
    : public AActor
{
    GENERATED_BODY()

public:

    AForestDirector();

protected:

    virtual void BeginPlay() override;

public:

    virtual void Tick(float DeltaTime) override;

private:

    FStoryData Story;

    float CurrentTime;

    int32 CurrentEventIndex;

    void LoadStory();

    void ExecuteEvent(
        const FStoryEvent& Event);

public:

    UPROPERTY(EditAnywhere)
    ACameraManager* CameraManager;

    UPROPERTY(EditAnywhere)
    AShadowActor* Shadow;

    UPROPERTY(EditAnywhere)UPROPERTY(EditAnywhere)
AWhisperSystem* Whisper;
    ALeoCharacter* Leo;

    UPROPERTY(EditAnywhere)
    ADayNightSystem* DayNight;

    UPROPERTY(EditAnywhere)
    AWhisperSystem* Whisper;

};
