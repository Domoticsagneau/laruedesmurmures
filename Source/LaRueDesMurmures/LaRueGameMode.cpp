#include "LaRueGameMode.h"
#include "LaRueDesMurmures.h"
#include "GameFramework/DefaultPawn.h"

ALaRueGameMode::ALaRueGameMode()
{
    DefaultPawnClass = ADefaultPawn::StaticClass();
}
