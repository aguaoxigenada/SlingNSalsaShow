// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SLINGNSALSASHOW_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMyAnimInstance();
	// This boolean can be seen and changed in the Animation Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	bool bIsBeingClicked;

	void SetIsBeingClicked(bool clickOnPlayer);
};
