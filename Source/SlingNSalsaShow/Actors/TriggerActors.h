// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActors.generated.h"

class AMyPawn;
class ASlingNSalsaShowGameMode;
class UBoxComponent;

UCLASS()
class SLINGNSALSASHOW_API ATriggerActors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlapMyPawn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlapMyPawn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckObjectsPassedPoint(AMyPawn* MyPawn);

	UFUNCTION()
		void HandleDestruction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* BoxCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystemComponent* FancyParticles = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* SpancyParticles = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	ASlingNSalsaShowGameMode* SlingGameMode;



};
