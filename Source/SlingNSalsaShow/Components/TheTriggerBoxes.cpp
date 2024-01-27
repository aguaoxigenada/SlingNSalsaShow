#include "TheTriggerBoxes.h"
#include "PlatformMovement.h"

// Sets default values for this component's properties
UTheTriggerBoxes::UTheTriggerBoxes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTheTriggerBoxes::BeginPlay()
{
    Super::BeginPlay();
    SetPlatform(ChoosenPlatform.Get());

}


void UTheTriggerBoxes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Platform == nullptr) return;

    AActor* Actor = GetAcceptableActor();

    if (Actor != nullptr)
    {
      //  CheckedPlayer = CheckIfActorIsPlayer(Actor);
        /*
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component != nullptr && !CheckedPlayer)
        {
            Component->SetSimulatePhysics(false);
           // Actor->AttachToComponent(FAttachmentTransformRules::KeepWorldTransform);
        }
        */
        Platform->SetShouldMove(true);
    }

    else
    {
        // Podriamos hacer que simplemente rompa cosas y listo.
        Platform->SetShouldMove(false);
    }
}

/*
bool UTheTriggerBoxes::CheckIfActorIsPlayer(AActor* Player)
{
    if (Player == nullptr) return false;

    bIsPlayer = Player->ActorHasTag("ThePlayer");
    return bIsPlayer;
}
*/
void UTheTriggerBoxes::SetPlatform(AActor* ThePlatform)
{
    if (ThePlatform == nullptr) return;

    TArray<UActorComponent*> Components;

    ThePlatform->GetComponents(Components);

    for (UActorComponent* Comp : Components)
    {
        UPlatformMovement* thisComp = Cast<UPlatformMovement>(Comp);
        if (thisComp)
        {
            Platform = thisComp;
        }
    }
}

AActor* UTheTriggerBoxes::GetAcceptableActor() const
{
    TArray<AActor*> Actors;

    GetOwner()->GetOverlappingActors(Actors);
   
    for (AActor* Actor : Actors)
    {
        if (Actor->ActorHasTag(AcceptableActorTag))
        {
            //UE_LOG(LogTemp, Warning, TEXT("Overlapping Correct Actor"));
            return Actor;
        }
    }
    return nullptr;
}

