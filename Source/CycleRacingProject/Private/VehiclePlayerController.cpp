// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePlayerController.h"
#include "VehicleGameMode.h"
#include "Kismet/GameplayStatics.h"

void AVehiclePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("RestartGame", IE_Pressed, this, &AVehiclePlayerController::RestartLevel);
	InputComponent->BindAction("RestartPlayer", IE_Pressed, this, &AVehiclePlayerController::RestartPlayer);
}

void AVehiclePlayerController::RestartPlayer()
{
	AVehicleGameMode* CycleRacingGameMode = Cast<AVehicleGameMode>(UGameplayStatics::GetGameMode(this));
	CycleRacingGameMode->RestartPlayer(this);
}