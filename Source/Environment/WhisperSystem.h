
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhisperSystem.generated.h"

class USoundBase;

UCLASS()
class LARUEDESMURMURES_API AWhisperSystem
    : public AActor
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere)
    TArray<USoundBase*> WhisperSounds;

    UFUNCTION()
    void PlayWhisper(
        FVector Location);

    UFUNCTION()
    void PlayRandomWhisper(
        FVector AroundLocation,
        float Radius);
};
