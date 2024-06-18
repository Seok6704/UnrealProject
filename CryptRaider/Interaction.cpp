// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UInteraction::UInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteraction::BeginPlay()
{
	Super::BeginPlay();

	InitMap();
}


// Called every frame
void UInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	NowInteract = GetInteractInReach(HitResult);
}


bool UInteraction::isInteract() const// 상호 작용 가능 여부 리턴
{
	return NowInteract;
}

void UInteraction::OnInteraction() // 상호 작용 진행
{
	for(auto& Key : InterKeyMap)
	{
		if(HitResult.GetActor()->ActorHasTag(Key.Key))
		{
			int32 NowKey = Key.Value;
			switch (NowKey)
			{
				case 0: // Door
					SetOpener(HitResult.GetActor()->GetComponentByClass<UDoorOpener>()); // 해당 클래스를 가지고 있는 오브젝트를 반환
					if(Opener) Opener->DoorOpen(true);
					break;
			}
			break;
		}
	}
}

bool UInteraction::GetInteractInReach(FHitResult& OutHitResult) const // 상호작용 대상 탐색
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * InteractDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractRadius);

	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel3,
		Sphere
	);
}

void UInteraction::SetOpener(UDoorOpener* NewOpener) // 의존성 주입
{
	Opener = NewOpener;
}

void UInteraction::InitMap()
{
	InterKeyMap.Add("Door", 0);
}

