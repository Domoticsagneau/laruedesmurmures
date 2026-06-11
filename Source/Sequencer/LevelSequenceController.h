#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSequenceController.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;
class ALevelSequenceActor;

USTRUCT()
struct FNamedSequence
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FString SequenceName;

    UPROPERTY(EditAnywhere)
    ULevelSequence* Sequence = nullptr;
};

UCLASS()
class LARUEDESMURMURES_API ALevelSequenceController
    : public AActor
{
    GENERATED_BODY()

public:

    ALevelSequenceController();

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere)
    TArray<FNamedSequence> Sequences;

    UFUNCTION()
    void PlaySequence(
        const FString& SequenceName);

    UFUNCTION()
    void StopSequence();

private:

    UPROPERTY()
    ULevelSequencePlayer* CurrentPlayer;

    UPROPERTY()
    ALevelSequenceActor* CurrentActor;

    ULevelSequence*
    FindSequence(
        const FString& Name);
};
