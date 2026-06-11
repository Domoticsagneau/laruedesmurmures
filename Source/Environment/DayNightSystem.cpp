#include "DayNightSystem.h"

#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"

ADayNightSystem::ADayNightSystem()
{
    PrimaryActorTick.bCanEverTick = true;

    bSunset = false;
    bNight = false;
}

void ADayNightSystem::Tick(
    float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bSunset && Sun)
    {
        float Current =
            Sun->GetLightComponent()
            ->Intensity;

        Current -= DeltaTime * 0.4f;

        Sun->GetLightComponent()
            ->SetIntensity(Current);
    }

    if (bNight && Sun)
    {
        float Current =
            Sun->GetLightComponent()
            ->Intensity;

        Current -= DeltaTime * 1.2f;

        Sun->GetLightComponent()
            ->SetIntensity(Current);
    }
  
    if (Fog)
    {
      float Density =
      FMath::Lerp(
            0.02f,
            0.08f,
            Current / 10.f);

      Fog->GetComponent()
        ->SetFogDensity(
            Density);
    }
}

void ADayNightSystem::StartSunset()
{
    bSunset = true;
}

void ADayNightSystem::StartNight()
{
    bNight = true;
}



