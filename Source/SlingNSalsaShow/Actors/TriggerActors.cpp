
#include "TriggerActors.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
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
	FancyParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticles"));
	FancyParticles->SetupAttachment(RootComponent);

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
void ATriggerActors::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SlingGameMode->ActorDied(this);
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
}
