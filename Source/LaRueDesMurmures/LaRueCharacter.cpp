#include "LaRueCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ALaRueCharacter::ALaRueCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
    bReplicates = true;
}

void ALaRueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ALaRueCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight",   this, &ALaRueCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn",        this, &ALaRueCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp",      this, &ALaRueCharacter::LookUp);
}

void ALaRueCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.f)
        AddMovementInput(GetActorForwardVector(), Value);
}

void ALaRueCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.f)
        AddMovementInput(GetActorRightVector(), Value);
}

void ALaRueCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ALaRueCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}
