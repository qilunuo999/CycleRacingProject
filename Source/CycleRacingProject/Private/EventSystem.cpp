// Fill out your copyright notice in the Description page of Project Settings.


#include "EventSystem.h"

AEventSystem* AEventSystem::SingletonInstance = nullptr;

AEventSystem::AEventSystem(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void AEventSystem::BroadcastStopCarEvent()
{
	StopCarEvent.Broadcast();
}

void AEventSystem::BroadcastPlayGameEvent()
{
	InitEvent.Broadcast(true);
}

void AEventSystem::BroadcastResetCarEngineRMPEvent()
{
	ResetCarEngineRMP.Broadcast();
}