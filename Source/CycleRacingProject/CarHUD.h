// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CarHUD.generated.h"

/**
 * 
 */
UCLASS()
class CYCLERACINGPROJECT_API ACarHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACarHUD();
	/** Font used to render the vehicle info */
	UPROPERTY()
		UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
