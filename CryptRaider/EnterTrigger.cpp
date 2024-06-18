// Fill out your copyright notice in the Description page of Project Settings.


#include "EnterTrigger.h"

UEnterTrigger::UEnterTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UEnterTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void UEnterTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Actor = GetPlayer();
    if(Actor != nullptr)
    {
        isEnter = true;
        SetComponentTickEnabled(false); // 더이상 TickComponent를 사용할 필요가 없음
    }
}

AActor* UEnterTrigger::GetPlayer() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for(AActor* Actor : Actors)
    {
        if(Actor->ActorHasTag(PlayerTag))
        {
            return Actor;
        }
    }

    return nullptr;
}

bool UEnterTrigger::isEnterPlayer() const
{
    return isEnter;
}

void UEnterTrigger::TriggerActivate()
{
    SetComponentTickEnabled(true);
}