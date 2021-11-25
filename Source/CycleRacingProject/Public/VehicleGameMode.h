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

	// ��Ϸ��ʼ����ʱ
	int CountTime;

public:
	virtual void StartPlay() override;

	EGameState CurrentGameState;

private:
	// ����ʱUI
	UUserWidget* CutTimeWidget;

	// ��Ϸ����ʱUI���ڵ�
	UCanvasPanel* RootPanel;

	// ��ǰ��Ϸʣ��ʱ��UI
	UTextBlock* RemainingTime;

	// ��ǰ��Ϸ״̬
	UBorder* GameStateBorder;

	// ����ʱ��UI
	UTextBlock* RewardTime;

	//�¼�ϵͳ
	AEventSystem* EventSystem;

	// ��ǰʣ����Ϸʱ��
	float CurrentRemainingTime;

	// ��Ϸ�Ƿ�ʧ��
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
