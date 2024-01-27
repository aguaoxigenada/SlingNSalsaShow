// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObjects.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCubeReceiveDamage, int, CurrentLife);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCubeDeath);

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class SLINGNSALSASHOW_API AMovingObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingObjects();

	UPROPERTY(BlueprintAssignable)
	FOnCubeReceiveDamage OnCubeReceiveDamage;

	UPROPERTY(BlueprintAssignable)
	FOnCubeDeath OnCubeDeath;

	UFUNCTION(BlueprintCallable)
	void GetDamage(int Damage);


	UFUNCTION()
	void HandleDestruction();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetCurrentLife() { return CurrentLife; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetMaxLife() { return MaxLife; };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ExplosionParticle = nullptr;

	UPROPERTY(EditAnywhere)
	bool canRotate;

	UFUNCTION()
	void RotatePlatform(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLife = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentLife;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GetDamageEvent(int ActualCurrentLife);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class SlingNSalsaShowGameMode* SlingNSalsaGameMode;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator RotationVelocity;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;


};
