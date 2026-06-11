#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LeoCharacter.generated.h"

UCLASS()
class LARUEDESMURMURES_API ALeoCharacter
    : public ACharacter
{
    GENERATED_BODY()

public:

    ALeoCharacter();

    virtual void Tick(float DeltaTime) override;

protected:

    virtual void BeginPlay() override;

private:

    bool bWalking;
    bool bRunning;

public:

    UFUNCTION()
    void WalkForward();

    UFUNCTION()
    void RunForward();

    UFUNCTION()
    void StopMovement();

    UFUNCTION()
    void LookBehind();
};
