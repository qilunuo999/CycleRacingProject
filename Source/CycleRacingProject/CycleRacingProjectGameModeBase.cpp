// Copyright Epic Games, Inc. All Rights Reserved.


#include "CycleRacingProjectGameModeBase.h"
#include "CarHUD.h"
#include "CarWheeledVehiclePawn.h"

ACycleRacingProjectGameModeBase::ACycleRacingProjectGameModeBase()
{
	DefaultPawnClass = ACarWheeledVehiclePawn::StaticClass();
	HUDClass = ACarHUD::StaticClass();
}