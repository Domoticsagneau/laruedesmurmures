#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LaRueCharacter.generated.h"

UCLASS()
class LARUEDESMURMURES_API ALaRueCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ALaRueCharacter();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
};
