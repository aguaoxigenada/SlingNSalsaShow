// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPawn.h"
#include "GameFramework/Actor.h"
#include "JumperActor.generated.h"

UCLASS()
class SLINGNSALSASHOW_API AJumperActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumperActor();
	UFUNCTION()
	void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEndLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;
	
	UPROPERTY(EditInstanceOnly, Category = "DashPad")
	float LaunchStrength;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float TimeInAir = 0.3f;
	void Jumped();
	AMyPawn* Player = nullptr;
	bool bCanLaunchCharacter = true;
};
