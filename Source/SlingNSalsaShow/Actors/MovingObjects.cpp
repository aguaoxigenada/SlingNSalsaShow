#include "MovingObjects.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingObjects::AMovingObjects()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a root scene component
	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	// Init Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootSceneComponent);

	// Init BoxComponent
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollision->SetupAttachment(Mesh);
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));

	// Create a particle system
	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticles"));
	ExplosionParticle->SetupAttachment(RootSceneComponent);

	// Set the initial position of the actor to the world origin (center)
	SetActorLocation(FVector::ZeroVector);

	CurrentLife = MaxLife;
}

void AMovingObjects::BeginPlay()
{
	Super::BeginPlay();
	ExplosionParticle->SetHiddenInGame(true);
}

void AMovingObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (canRotate) RotatePlatform(DeltaTime);
}

void AMovingObjects::GetDamage(int Damage)
{
	CurrentLife -= Damage;
	ExplosionParticle->SetHiddenInGame(false);
	TimerDelegate.BindLambda([&]
		{
			// Desaparece el Fueguito encima del cubo en 3 sec
			ExplosionParticle->SetHiddenInGame(true);
		});

	if (CurrentLife > 0)
	{
		// Podria cambiar de animacion o cualquier otra cosa del cubo.
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 3, false);
	}
	else
	{
		//		BomberKiddoGameMode->ActorDied(this);
		Destroy();
	}
}

void AMovingObjects::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
//	UE_LOG(LogTemp, Warning, TEXT("This is a warning message"));
}

void AMovingObjects::HandleDestruction()
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

