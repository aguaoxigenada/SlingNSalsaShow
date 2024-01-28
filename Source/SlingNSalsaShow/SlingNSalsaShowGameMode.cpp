// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlingNSalsaShowGameMode.h"
#include "UObject/ConstructorHelpers.h"


ASlingNSalsaShowGameMode::ASlingNSalsaShowGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Pawn/BP_BomberKiddoCharacter"));

    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

void ASlingNSalsaShowGameMode::BeginPlay()
{
    Super::BeginPlay();

}

void ASlingNSalsaShowGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor->ActorHasTag("Wave1")) BP_SpawnNewObjective(0);
	if (DeadActor->ActorHasTag("Wave2")) BP_SpawnNewObjective(1);
    if (DeadActor->ActorHasTag("Wave3")) BP_SpawnNewObjective(2);
	if (DeadActor->ActorHasTag("Wave4"))  BP_SpawnNewObjective(3);
}

