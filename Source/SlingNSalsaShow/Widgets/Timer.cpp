#include "Timer.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UTimer::NativeOnInitialized()
{
	//HudTimer = (UTextBlock*)(WidgetTree->FindWidget(TimerTextName));
	GameTimer();
	RepeatingCallsRemaining = TimerCount;
}

void UTimer::GameTimer()
{

	// Start Repeating function
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTimer::RepeatingVisualTimer, 1.0f, true, 0.f);

}

void UTimer::PlayLoseSound()
{
	if (LoseSound)
	{
		UGameplayStatics::PlaySound2D(this, LoseSound);
	}
}

void UTimer::RepeatingVisualTimer()
{

	if (--RepeatingCallsRemaining <= 0 )
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		OnPlayerLost();
	}

	TimerCount--;

	// Setear el timer al Texto
	HudTimer->SetText(FText::FromString(FString::FromInt(TimerCount)));

}
