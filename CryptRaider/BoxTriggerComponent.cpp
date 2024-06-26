// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTriggerComponent.h"

// Sets default values for this component's properties
UBoxTriggerComponent::UBoxTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false; // Room1 게임 시작 전에는 Tick 사용 X

	// ...
}


// Called when the game starts
void UBoxTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBoxTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
    if(Actor != nullptr)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if(Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		isOper = true;
    }
	else isOper = false;
}

bool UBoxTriggerComponent::isOnTrigger() const
{
	return isOper;
}

AActor* UBoxTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for(AActor* Actor : Actors)
	{
		if(Actor->ActorHasTag(AcceptableActorTag) && !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}
	}

	return nullptr;
}

void UBoxTriggerComponent::TriggerActivate()
{
	SetComponentTickEnabled(true);
}


