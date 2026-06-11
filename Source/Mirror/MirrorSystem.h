#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MirrorSystem.generated.h"

class ACameraManager;
class AShadowActor;
class ALeoCharacter;
class AActor;

UCLASS()
class LARUEDESMURMURES_API AMirrorSystem
    : public AActor
{
    GENERATED_BODY()

public:

    AMirrorSystem();

protected:

    virtual void BeginPlay() override;

public:

    UFUNCTION()
    void StartMirrorReveal();

    UFUNCTION()
    void BreakMirror();

    UFUNCTION()
    void EndSequence();

public:

    UPROPERTY(EditAnywhere)
    AActor* MirrorMesh;

    UPROPERTY(EditAnywhere)
    AShadowActor* Shadow;

    UPROPERTY(EditAnywhere)
    ALeoCharacter* Leo;

    UPROPERTY(EditAnywhere)
    ACameraManager* CameraManager;

private:

    bool bRevealStarted;
};
