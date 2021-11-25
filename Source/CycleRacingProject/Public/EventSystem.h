// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "EventSystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CYCLERACINGPROJECT_API AEventSystem : public AActor
{
	GENERATED_BODY()
	
public:
	AEventSystem(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "DelegateActor")
	static AEventSystem* GetInstance()
	{
		if (AEventSystem::SingletonInstance == nullptr)
		{
			AEventSystem::SingletonInstance = NewObject<AEventSystem>(GEngine->GameSingleton);
		}
		return AEventSystem::SingletonInstance;
	}

	DECLARE_EVENT(AEventSystem, FStopCarDelegate)
	DECLARE_EVENT(AEventSystem, FResetCarEngineRMP)
	DECLARE_EVENT_OneParam(AEventSystem, FCarDelegate, bool)

	FCarDelegate& OnPlayGameEvent() { return InitEvent; }
	FStopCarDelegate& OnStopCarEvent() { return StopCarEvent; }
	FResetCarEngineRMP& OnResetCarEngineRMPEvent() { return ResetCarEngineRMP; }

	void BroadcastStopCarEvent();

	void BroadcastPlayGameEvent();

	void BroadcastResetCarEngineRMPEvent();

private:
	static AEventSystem* SingletonInstance;

	FCarDelegate InitEvent;

	FStopCarDelegate StopCarEvent;

	FResetCarEngineRMP ResetCarEngineRMP;
};
