// Copyright Epic Games, Inc. All Rights Reserved.


#include "CycleRacingProjectGameModeBase.h"
#include "CarHUD.h"
#include "CarWheeledVehiclePawn.h"
#include "Public/VehiclePlayerController.h"

ACycleRacingProjectGameModeBase::ACycleRacingProjectGameModeBase()
{
	DefaultPawnClass = ACarWheeledVehiclePawn::StaticClass();
	HUDClass = ACarHUD::StaticClass();
	PlayerControllerClass = AVehiclePlayerController::StaticClass();
}