// Fill out your copyright notice in the Description page of Project Settings.


#include "JumperActor.h"

// Sets default values
AJumperActor::AJumperActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	//MeshComp->SetupAttachment(OverlapComp);

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	OverlapComp->SetupAttachment(MeshComp);
	OverlapComp->SetGenerateOverlapEvents(true);
	OverlapComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AJumperActor::OverlapLaunchPad);
	OverlapComp->OnComponentEndOverlap.AddUniqueDynamic(this, &AJumperActor::OverlapEndLaunchPad);
	LaunchStrength = 450.f;
}

// Called when the game starts or when spawned
void AJumperActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumperActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJumperActor::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AMyPawn>(OtherActor);

	if (Player && bCanLaunchCharacter)
	{
		const FVector impulse = Player->GetImpulse();
		const FVector scaledUpVector = GetActorUpVector();

		const float launchStrength = FMath::FRandRange(LaunchStrength*0.75, LaunchStrength*2.f);
		
		Player->LaunchPlayer((impulse + scaledUpVector).GetSafeNormal(), launchStrength);

		UE_LOG(LogTemp, Warning, TEXT("=======> LAUNCHING PLAYER +++<======== %f"), launchStrength);
		bCanLaunchCharacter = false;
	}
}

void AJumperActor::OverlapEndLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Player = Cast<AMyPawn>(OtherActor);
	if (Player)
	{
		bCanLaunchCharacter = true;
		UE_LOG(LogTemp, Warning, TEXT("=======> END OVERLAP <========"));
	}
}