// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EventSystem.h"

AVehicleGameMode::AVehicleGameMode()
{
	CountTime = 3;
}

void AVehicleGameMode::CutTime()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(CountTime));


	UCanvasPanel* RootPanel = Cast<UCanvasPanel>(CutTimeWidget->GetRootWidget());
	UBorder* Border1 = nullptr;
	UBorder* Border2 = nullptr;
	UVerticalBox* VerticleBox = nullptr;
	UTextBlock* CutTimeText = nullptr;

	if (RootPanel)
	{
		Border1 = Cast<UBorder>(RootPanel->GetChildAt(0));
		Border2 = Cast<UBorder>(RootPanel->GetChildAt(1));
		VerticleBox = Cast<UVerticalBox>(Border1->GetChildAt(0));
		CutTimeText = Cast<UTextBlock>(VerticleBox->GetChildAt(1));
	}

	CountTime--;
	if (CountTime == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_TimeCount);
		Border1->SetVisibility(ESlateVisibility::Hidden);
		Border2->SetVisibility(ESlateVisibility::Visible);
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
	GetWorldTimerManager().SetTimer(TimerHandle_TimeCount, this, &AVehicleGameMode::CutTime, 1.0f, true, 1.0f);
	FString WidgetClassLoadPath = FString(TEXT("/Game/HUD/WBP_CutTime.WBP_CutTime_C"));
	UClass* Widget = LoadClass<UUserWidget>(NULL, *WidgetClassLoadPath);
	CutTimeWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
	CutTimeWidget->AddToViewport();
}

void AVehicleGameMode::PlayGame()
{
	CutTimeWidget->RemoveFromParent();
	UEventSystem* EventSystem = UEventSystem::GetInstance();
	if (EventSystem)
	{
		if (&(EventSystem->OnInitialize()) != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Reference is not null!"));
			if (EventSystem->OnInitialize().IsBound())
			{
				EventSystem->OnInitialize().Broadcast(true);
				EventSystem->OnInitialize().Clear();
			}
		}
	}
}
