// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EventSystem.h"
#include "Styling/StyleColors.h"

AVehicleGameMode::AVehicleGameMode()
{
	CountTime = 3;
	CurrentRemainingTime = 30.0f;
	CurrentGameState = EGameState::EWait;
	IsGameLose = false;
}

void AVehicleGameMode::CutTime()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(CountTime));
	UBorder* Border1 = nullptr;
	GameStateBorder = nullptr;
	UVerticalBox* VerticleBox = nullptr;
	UTextBlock* CutTimeText = nullptr;

	if (RootPanel)
	{
		Border1 = Cast<UBorder>(RootPanel->GetChildAt(0));
		GameStateBorder = Cast<UBorder>(RootPanel->GetChildAt(1));
		VerticleBox = Cast<UVerticalBox>(Border1->GetChildAt(0));
		CutTimeText = Cast<UTextBlock>(VerticleBox->GetChildAt(1));
	}

	CountTime--;
	if (CountTime == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_TimeCount);
		Border1->SetVisibility(ESlateVisibility::Hidden);
		GameStateBorder->SetVisibility(ESlateVisibility::Visible);
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = "PlayGame";
		LatentInfo.Linkage = 1;
		LatentInfo.UUID = 1000000;
		UKismetSystemLibrary::Delay(this, 1.0f, LatentInfo);
	}
	if (CutTimeText)
	{
		CutTimeText->SetText(FText::FromString(FString::FromInt(CountTime)));
	}
}

void AVehicleGameMode::StartPlay()
{
	Super::StartPlay();
	
	FString WidgetClassLoadPath = FString(TEXT("/Game/HUD/WBP_CutTime.WBP_CutTime_C"));
	UClass* Widget = LoadClass<UUserWidget>(NULL, *WidgetClassLoadPath);
	CutTimeWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
	CutTimeWidget->AddToViewport();
	RootPanel = Cast<UCanvasPanel>(CutTimeWidget->GetRootWidget());
	UUserWidget* W_Minimap = Cast<UUserWidget>(RootPanel->GetChildAt(3));
	UFunction* SetOwnerAndStartUpdate = W_Minimap->FindFunction(FName(TEXT("SetOwnerAndStartUpdate")));
	if (SetOwnerAndStartUpdate)
	{
		struct FParams
		{
			APawn* OwnerRef;
			bool StartUpdate;
		};
		FParams Params;
		Params.OwnerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
		Params.StartUpdate = true;
		W_Minimap->ProcessEvent(SetOwnerAndStartUpdate, &Params);
	}
	GetWorldTimerManager().SetTimer(TimerHandle_TimeCount, this, &AVehicleGameMode::CutTime, 1.0f, true, 1.0f);
}

void AVehicleGameMode::PlayGame()
{
	if (GameStateBorder)
	{
		GameStateBorder->SetVisibility(ESlateVisibility::Hidden);
	}
	EventSystem = AEventSystem::GetInstance();
	CurrentGameState = EGameState::EPlaying;
	GetWorldTimerManager().SetTimer(TimerHandle_TimeCount, this, &AVehicleGameMode::CutRemaingTime, 1.f, true, 1.f);
}

void AVehicleGameMode::CutRemaingTime()
{
	CurrentRemainingTime -= 1.f;

	RootPanel = Cast<UCanvasPanel>(CutTimeWidget->GetRootWidget());
	UBorder* RemainingTimeBorder = nullptr;
	RemainingTime = nullptr;

	if (RootPanel)
	{
		RemainingTimeBorder = Cast<UBorder>(RootPanel->GetChildAt(2));
		UHorizontalBox* HorizontalBox = Cast<UHorizontalBox>(RemainingTimeBorder->GetChildAt(0));
		RemainingTime = Cast<UTextBlock>(HorizontalBox->GetChildAt(0));
		RewardTime = Cast<UTextBlock>(HorizontalBox->GetChildAt(1));
	}

	if (CurrentRemainingTime == 0.0f)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_TimeCount);
		GameLose();
	}

	if (RemainingTime)
	{

		if (CurrentRemainingTime < 20.0f)
		{
			RemainingTime->SetColorAndOpacity(FSlateColor(EStyleColor::AccentYellow));
		}
		else if (CurrentRemainingTime < 10.0f)
		{
			RemainingTime->SetColorAndOpacity(FSlateColor(EStyleColor::AccentRed));
		}
		else
		{
			RemainingTime->SetColorAndOpacity(FSlateColor(FColor(94, 255, 97)));
		}
		RemainingTime->SetText(FText::FromString(FString::SanitizeFloat(CurrentRemainingTime) + "S"));
	}
}

void AVehicleGameMode::GameLose()
{
	IsGameLose = true;

	if (GameStateBorder)
	{
		GameStateBorder->SetVisibility(ESlateVisibility::Visible);
		UTextBlock* GameStateText = Cast<UTextBlock>(GameStateBorder->GetChildAt(0));
		GameStateText->SetText(FText::FromString(FString("You Lose")));
		GameStateText->SetColorAndOpacity(FSlateColor(EStyleColor::AccentGray));
		CurrentGameState = EGameState::EForceStop;
	}
}

void AVehicleGameMode::AddRemainingTime(float value)
{
	CurrentRemainingTime += value;
	if (RewardTime)
	{
		RewardTime->SetVisibility(ESlateVisibility::Visible);
		RewardTime->SetText(FText::FromString("+ " + FString::SanitizeFloat(value) + "S"));
		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([&]
		{
			RewardTime->SetVisibility(ESlateVisibility::Hidden);
			GetWorldTimerManager().ClearTimer(TimerHandle_RewardTimeDisplay);
		});
		GetWorldTimerManager().SetTimer(TimerHandle_RewardTimeDisplay, TimerCallback, 3.0f, false);
	}
}

void AVehicleGameMode::GameVictory()
{
	if (GameStateBorder)
	{
		GameStateBorder->SetVisibility(ESlateVisibility::Visible);
		UTextBlock* GameStateText = Cast<UTextBlock>(GameStateBorder->GetChildAt(0));
		GameStateText->SetText(FText::FromString(FString("You WIN!!!")));
		GameStateText->SetColorAndOpacity(FSlateColor(EStyleColor::AccentYellow));
		GetWorldTimerManager().ClearTimer(TimerHandle_TimeCount);
		RemainingTime->SetVisibility(ESlateVisibility::Hidden);
		CurrentGameState = EGameState::EForceStop;
	}
}