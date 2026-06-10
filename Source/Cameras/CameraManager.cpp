#include "CameraManager.h"

#include "CineCameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ACameraManager::ACameraManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACameraManager::BeginPlay()
{
    Super::BeginPlay();
}
ACineCameraActor*
ACameraManager::FindCamera(
    const FString& CameraName)
{
    for (const FNamedCamera& Entry : Cameras)
    {
        if (Entry.CameraName == CameraName)
        {
            return Entry.Camera;
        }
    }

    return nullptr;
}
void ACameraManager::SwitchCamera(
    int32 Index)
{
    if (!Cameras.IsValidIndex(Index))
    {
        return;
    }

    auto* PC =
        UGameplayStatics
        ::GetPlayerController(
            GetWorld(),
            0);

    if (!PC)
    {
        return;
    }

    PC->SetViewTarget(
        Cameras[Index].Camera);
}
void ACameraManager::SwitchCameraByName(
    const FString& CameraName)
{
    ACineCameraActor* Camera =
        FindCamera(CameraName);

    if (!Camera)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Camera not found: %s"),
            *CameraName);

        return;
    }

    auto* PC =
        UGameplayStatics
        ::GetPlayerController(
            GetWorld(),
            0);

    if (!PC)
    {
        return;
    }

    PC->SetViewTarget(Camera);
}
void ACameraManager::BlendToCamera(
    const FString& CameraName,
    float BlendTime)
{
    ACineCameraActor* Camera =
        FindCamera(CameraName);

    if (!Camera)
    {
        return;
    }

    auto* PC =
        UGameplayStatics
        ::GetPlayerController(
            GetWorld(),
            0);

    if (!PC)
    {
        return;
    }

    PC->SetViewTargetWithBlend(
        Camera,
        BlendTime);
}


