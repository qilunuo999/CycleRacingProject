// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventSystem.generated.h"

/**
 * 
 */
UCLASS()
class CYCLERACINGPROJECT_API UEventSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UEventSystem();
	static UEventSystem* GetInstance()
	{
		if (UEventSystem::SingletonInstance == nullptr)
		{
			UEventSystem::SingletonInstance = NewObject<UEventSystem>();
		}
		return UEventSystem::SingletonInstance;
	}

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCarDelegate, bool, GameState);

	UPROPERTY(BlueprintAssignable, Category = "DelegateActor")
	FCarDelegate InitEvent;

	FCarDelegate& OnInitialize() { return InitEvent; }

private:
	static UEventSystem* SingletonInstance;
};
