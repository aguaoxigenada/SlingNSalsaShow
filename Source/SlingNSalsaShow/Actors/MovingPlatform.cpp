#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ActiveTriggers > 0)
	{
		if(HasAuthority() /*&& bCanMove*/) 
		{
			FVector Location = GetActorLocation();
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if(JourneyTravelled >= JourneyLength)
			{
				FVector Swap =  GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
				
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location +=  Speed * DeltaTime * Direction;
			SetActorLocation(Location);		
		}
	}

}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
	//bCanMove = !bCanMove;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if(ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
	
	//bCanMove = !bCanMove;
}



/* My Way Worked!
	
	if(HasAuthority()) 
	{
		FVector Location = GetActorLocation();
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location +=  Speed * DeltaTime * Direction;
		float Distance = FVector::Distance(Location, GlobalTargetLocation);

		UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), Distance);

		if(FVector::Dist(Location, GlobalTargetLocation) <= 1)
		{
			OldLocation =  GlobalTargetLocation;
			GlobalTargetLocation = GlobalStartLocation;
			GlobalStartLocation = OldLocation;
		}

		SetActorLocation(Location);		
	}
	*/
