// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlingNSalsaShowGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerWin);

UCLASS(minimalapi)
class ASlingNSalsaShowGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASlingNSalsaShowGameMode();
	void ActorDied(AActor* DeadActor);

	UPROPERTY(BlueprintAssignable)
	FOnPlayerWin OnPlayerWin;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SpawnNewObjective(int waveNum);

private:

	class ATriggerActors* Objective;
	class UBK_UIHudInGame* HudInGame;

	void HandleGameStart();

	int32 TargetTriggers = 0;
	int32 GetTargetCubeCount(int actualWave);

};


