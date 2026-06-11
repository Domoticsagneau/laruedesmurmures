#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerZone.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FTriggerActivated,
    FString,
    TriggerID);

UCLASS()
class LARUEDESMURMURES_API ATriggerZone
    : public AActor
{
    GENERATED_BODY()

public:

    ATriggerZone();

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere)
    FString TriggerID;

    UPROPERTY(EditAnywhere)
    bool bTriggerOnlyOnce = true;

    UPROPERTY(BlueprintAssignable)
    FTriggerActivated OnTriggerActivated;

private:

    UPROPERTY()
    UBoxComponent* TriggerBox;

    bool bAlreadyTriggered;

    UFUNCTION()
    void OnBeginOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
