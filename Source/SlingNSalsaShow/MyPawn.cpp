// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a root scene component
	//USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	
	
	// Init BoxComponent
	myBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	
	// Init Mesh
	myMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = myMesh;
	//myMesh->SetupAttachment(RootComponent);

	// Init BoxComponent
	myBoxCollision->SetupAttachment(myMesh);
	myBoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));

	myMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	myMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);

	myMesh->OnClicked.AddDynamic(this, &AMyPawn::OnClicked);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	//ThePlane = Plane.GetDefaultObject();
	//GetController()->OnReleased.AddDynamic(this, &AMyPawn::OnReleased);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check for some condition to trigger the impulse (e.g., a key press)
	if (bShouldApplyImpulse)
	{
		myMesh->AddImpulse(impulse, NAME_None, true);
		bShouldApplyImpulse = false;  // Reset the condition to avoid continuous impulses

		UE_LOG(LogTemp, Warning, TEXT("=======> bShouldApplyImpulse"));
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPawn::SetThePlane(AActor* LevelPlane)
{
	ThePlane = LevelPlane;
}

void AMyPawn::OnClicked(UPrimitiveComponent* UPrimitiveComponent, FKey ButtonPressed)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnClicked"));
	UE_LOG(LogTemp, Display, TEXT("OnClicked"));
}

void AMyPawn::OnReleased(AActor* UPrimitiveComponent, FKey ButtonReleased)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReleased"));

	FVector playerLocation =  GetActorLocation();
	EPairedAxis pairedAxis = ButtonReleased.GetPairedAxis();
	
	UE_LOG(LogTemp, Display, TEXT("Vector value: %s"), *playerLocation.ToString());
	
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController != nullptr)
	{
		float MouseX, MouseY;
		if (PlayerController->GetMousePosition(MouseX, MouseY))
		{
			//MouseX and MouseY now contain the position of the mouse

			FVector WorldLocation, WorldDirection;
			if (PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection))
			{
				// Raycast or use the direction to determine the world position
				FVector EndPoint = WorldLocation + (WorldDirection * 10000); // Arbitrary distance
				FHitResult HitResult;
				if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, EndPoint, ECC_Visibility))
				{
					FVector MouseWorldPosition = HitResult.Location;
					// MouseWorldPosition is the location in the world where the mouse is pointing
					UE_LOG(LogTemp, Display, TEXT("Mouse position value: %s"), *MouseWorldPosition.ToString());
					

					if(ThePlane)
					{
						FVector planePoint = FVector(-1200.f, -820.f, 0);
						FVector planeUpVector = ThePlane->GetActorUpVector(); 
						FVector projectedActorPoint = FVector::PointPlaneProject(playerLocation, planePoint, planeUpVector);
						FVector projectedMousePoint = FVector::PointPlaneProject(MouseWorldPosition, planePoint, planeUpVector);

						FVector forceDirection = projectedActorPoint.GetSafeNormal() - projectedMousePoint.GetSafeNormal();

						impulse = (forceDirection * 1000.f);

						bShouldApplyImpulse = true;
						// void DrawDebugDirectionalArrow
						// (
						//     const UWorld * InWorld,
						//     FVector const & LineStart,
						//     FVector const & LineEnd,
						//     float ArrowSize,
						//     FColor const & Color,
						//     bool bPersistentLines,
						//     float LifeTime,
						//     uint8 DepthPriority,
						//     float Thickness
						// )
						 UE_LOG(LogTemp, Warning, TEXT("=======> DRAWING ARROW"));
						 DrawDebugDirectionalArrow(GetWorld(), projectedMousePoint, projectedActorPoint, 1000.f, FColor::Red, true, 0.f, 5, 2.f);
					}
				}	
			}
		}	
	}
}

