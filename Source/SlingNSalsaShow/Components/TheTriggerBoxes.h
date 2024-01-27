// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheTriggerBoxes.generated.h"

class UPlatformMovement;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLINGNSALSASHOW_API UTheTriggerBoxes : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTheTriggerBoxes();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditInstanceOnly)
	FName AcceptableActorTag;

	virtual void BeginPlay() override;
	AActor* GetAcceptableActor() const;


private:
	UPROPERTY(EditInstanceOnly)
	TWeakObjectPtr<AActor> ChoosenPlatform;

	bool CheckIfActorIsPlayer(AActor* Player);
	void SetPlatform(AActor* ThePlatform);
	bool bIsPlayer;
	bool CheckedPlayer;

	UPlatformMovement* Platform;
};
