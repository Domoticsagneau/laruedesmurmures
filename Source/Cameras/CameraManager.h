#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraManager.generated.h"

class ACineCameraActor;

USTRUCT()
struct FNamedCamera
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FString CameraName;

    UPROPERTY(EditAnywhere)
    ACineCameraActor* Camera = nullptr;
};

UCLASS()
class LARUEDESMURMURES_API ACameraManager
    : public AActor
{
    GENERATED_BODY()

public:

    ACameraManager();

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, Category="Cameras")
    TArray<FNamedCamera> Cameras;

    UFUNCTION()
    void SwitchCamera(int32 Index);

    UFUNCTION()
    void SwitchCameraByName(
        const FString& CameraName);

    UFUNCTION()
    void BlendToCamera(
        const FString& CameraName,
        float BlendTime = 1.0f);

private:

    ACineCameraActor* FindCamera(
        const FString& CameraName);
};
