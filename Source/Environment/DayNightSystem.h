#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightSystem.generated.h"

class ADirectionalLight;
class AExponentialHeightFog;

UCLASS()
class LARUEDESMURMURES_API ADayNightSystem
    : public AActor
{
    GENERATED_BODY()

public:

    ADayNightSystem();

    virtual void Tick(float DeltaTime) override;

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere)
    ADirectionalLight* Sun;

    UPROPERTY(EditAnywhere)
    AExponentialHeightFog* Fog;

    UFUNCTION()
    void StartSunset();

    UFUNCTION()
    void StartNight();

private:

    bool bSunset;
    bool bNight;
};
