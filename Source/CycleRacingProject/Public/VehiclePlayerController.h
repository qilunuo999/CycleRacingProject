// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VehiclePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CYCLERACINGPROJECT_API AVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

private:
	void RestartPlayer();
};
