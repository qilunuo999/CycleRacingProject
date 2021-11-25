// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VehicleGameMode.generated.h"

class UCanvasPanel;
class UTextBlock;
class UBorder;
class AEventSystem;

enum class EGameState : short
{
	EWait,
	EPlaying,
	EForceStop
};

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class CYCLERACINGPROJECT_API AVehicleGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	AVehicleGameMode();

	FTimerHandle TimerHandle_TimeCount;

	FTimerHandle TimerHandle_RewardTimeDisplay;

	void CutTime();

	// 游戏开始倒计时
	int CountTime;

public:
	virtual void StartPlay() override;

	EGameState CurrentGameState;

private:
	// 倒计时UI
	UUserWidget* CutTimeWidget;

	// 游戏倒计时UI根节点
	UCanvasPanel* RootPanel;

	// 当前游戏剩余时间UI
	UTextBlock* RemainingTime;

	// 当前游戏状态
	UBorder* GameStateBorder;

	// 奖励时间UI
	UTextBlock* RewardTime;

	//事件系统
	AEventSystem* EventSystem;

	// 当前剩余游戏时间
	float CurrentRemainingTime;

	// 游戏是否失败
	bool IsGameLose;

	UFUNCTION()
	void PlayGame();

	UFUNCTION(BlueprintCallable)
	void AddRemainingTime(float value);

	UFUNCTION(BlueprintCallable)
	void GameVictory();

	void GameLose();

	void CutRemaingTime();
};
