// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class SLINGNSALSASHOW_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* myBoxCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* myMesh = nullptr;

	// Handler for when the actor is clicked
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedActor, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable)
	void SetThePlane(AActor* LevelPlane);

	// Handler for when the click is released
	UFUNCTION(BlueprintCallable)
	void OnReleased(AActor* TouchedActor, FKey ButtonReleased);
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

private:
	//UPROPERTY(EditAnywhere, Category = "Plane Ptr")
	//TSubclassOf<AActor> Plane;
	//TWeakObjectPtr<AActor> Plane
	
	AActor* ThePlane;
	bool bShouldApplyImpulse;
	FVector impulse;
};
