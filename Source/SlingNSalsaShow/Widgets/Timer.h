// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Timer.generated.h"

class UTextBlock;

UCLASS()
class SLINGNSALSASHOW_API UTimer : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeOnInitialized() override;



protected:
	UFUNCTION()
	void RepeatingVisualTimer();

	UFUNCTION(blueprintImplementableEvent)
	void OnPlayerLost();

	void GameTimer();

	void PlayWinSound();

	void PlayLoseSound();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HudTimer;

private:

	float StartDelay = 240.f;
	int TimerCount = 180;
	int RepeatingCallsRemaining;

	FTimerHandle GameOverTimerHandle;
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* WinSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LoseSound;
};
