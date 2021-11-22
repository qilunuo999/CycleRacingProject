// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VehicleGameMode.generated.h"

/**
 *
 */
UCLASS()
class CYCLERACINGPROJECT_API AVehicleGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	AVehicleGameMode();

	FTimerHandle TimerHandle_TimeCount;

	void CutTime();

	int CountTime;

public:
	virtual void StartPlay() override;

private:
	UUserWidget* CutTimeWidget;

	UFUNCTION()
		void PlayGame();
};
