// Fill out your copyright notice in the Description page of Project Settings.


#include "CarWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UCarWheelRear::UCarWheelRear()
{
	WheelRadius = 32.f;
	WheelWidth = 20.0f;
	FrictionForceMultiplier = 2.0f;
	CorneringStiffness = 500.0f;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	bAffectedBySteering = false;
	AxleType = EAxleType::Rear;
	SpringRate = 200.0f;
	SpringPreload = 100.f;
	SuspensionDampingRatio = 0.5f;
	WheelLoadRatio = 0.0f;
	RollbarScaling = 0.5f;
	SuspensionMaxRaise = 8;
	SuspensionMaxDrop = 12.0f;
	WheelLoadRatio = 0.5f;
	SuspensionDampingRatio = 0.3f;
}