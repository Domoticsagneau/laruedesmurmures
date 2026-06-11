#include "LeoCharacter.h"

ALeoCharacter::ALeoCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bWalking = false;
    bRunning = false;
}

void ALeoCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ALeoCharacter::Tick(
    float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bWalking)
    {
        AddMovementInput(
            GetActorForwardVector(),
            1.0f);
    }

    if (bRunning)
    {
        AddMovementInput(
            GetActorForwardVector(),
            2.0f);
    }
}

void ALeoCharacter::WalkForward()
{
    bWalking = true;
    bRunning = false;

    GetCharacterMovement()
        ->MaxWalkSpeed = 180.f;
}

void ALeoCharacter::RunForward()
{
    bRunning = true;
    bWalking = false;

    GetCharacterMovement()
        ->MaxWalkSpeed = 420.f;
}

void ALeoCharacter::StopMovement()
{
    bWalking = false;
    bRunning = false;
}

void ALeoCharacter::LookBehind()
{
    FRotator Rotation =
        GetActorRotation();

    Rotation.Yaw += 180.f;

    SetActorRotation(
        Rotation);
}

