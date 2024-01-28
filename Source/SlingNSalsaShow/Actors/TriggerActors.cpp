
#include "TriggerActors.h"

#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SlingNSalsaShow/MyPawn.h"
#include "SlingNSalsaShow/SlingNSalsaShowGameMode.h"

// Sets default values
ATriggerActors::ATriggerActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//init Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	//Init BoxComponent
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollision->SetupAttachment(Mesh);
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));

	// Create a particle system
	FancyParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FancyParticles"));
	FancyParticles->SetupAttachment(RootComponent);

	SpancyParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpancyParticles"));
	SpancyParticles->SetupAttachment(RootComponent);

	//BoxCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATriggerActors::OnBeginOverlapMyPawn);
	BoxCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ATriggerActors::OnEndOverlapMyPawn);
}

// Called when the game starts or when spawned
void ATriggerActors::BeginPlay()
{
	Super::BeginPlay();
	SlingGameMode = Cast<ASlingNSalsaShowGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ATriggerActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Function to handle begin overlap event
void ATriggerActors::OnBeginOverlapMyPawn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor->IsA(AMyPawn::StaticClass()))
	{
		HandleDestruction();
		
	}
}

void ATriggerActors::OnEndOverlapMyPawn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(AMyPawn::StaticClass()))
	{
		AMyPawn* ActorLocation = Cast<AMyPawn>(OtherActor);
		//FVector ActorLocation = OtherActor->GetActorLocation();
		//float xPosition = StaticCast<float>(ActorLocation.X);
		CheckObjectsPassedPoint(ActorLocation);

	}
}

void ATriggerActors::CheckObjectsPassedPoint(AMyPawn* MyPawn)
{
	// Iterate through all objects of your class
	//FVector thisLocation = this->GetActorLocation();
	//float thisXPosition = StaticCast<float>(thisLocation.X);
	float PawnsXPosition = MyPawn->GetActorLocation().X;

	/*if (abs(PawnsXPosition) > abs(thisXPosition))
	{
		HandleDestruction();
	}
	*/

	
	for (TActorIterator<ATriggerActors> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ATriggerActors* Object = *ActorItr;

		// Check if the X-coordinate of the object is greater than the reference X
		if (  FMath::Abs(PawnsXPosition) > FMath::Abs(Object && Object->GetActorLocation().X))
		{
			HandleDestruction();
		}
	}

}

void ATriggerActors::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	SlingGameMode->ActorDied(this);
	Destroy();
}
