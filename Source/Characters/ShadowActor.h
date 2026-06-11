#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShadowActor.generated.h"

UCLASS()
class LARUEDESMURMURES_API AShadowActor
    : public ACharacter
{
    GENERATED_BODY()

public:

    AShadowActor();

    UFUNCTION()
    void Appear();

    UFUNCTION()
    void Disappear();

    UFUNCTION()
    void TeleportToPoint(
        FVector Location);

    UFUNCTION()
    void MoveToward(
        FVector TargetLocation);

private:

    bool bMoving;

    FVector MoveTarget;
};
