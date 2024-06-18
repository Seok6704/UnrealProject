// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	GetDoorMeshComponent(Meshs);
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if(ShouldOpen) //문 각도 이슈(트렐로 참고) 발생으로 임시 비활성화
	// {
	// 	float Speed = OpenOffset.Yaw / OpenTime;

	// 	for(UMeshComponent* Component : Meshs)
	// 	{
	// 		USceneComponent* SComponent = Cast<USceneComponent>(Component);
	// 		if(Component->GetName() == LeftDoorName)
	// 		{
	// 			TargetRotation = OpenOffset;
	// 		}
	// 		else if(Component->GetName() == RightDoorName)
	// 		{
	// 			TargetRotation = OpenOffset * -1;
	// 		}

	// 		FRotator CurrentRotation = Component->GetComponentRotation();
	// 		FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, Speed);
	// 		UE_LOG(LogTemp, Display, TEXT("Current Rotation : %s"), *CurrentRotation.ToString());
	// 		UE_LOG(LogTemp, Display, TEXT("Target Rotation : %s"), *TargetRotation.ToString());
	// 		UE_LOG(LogTemp, Display, TEXT("New Rotation : %s"), *NewRotation.ToString());

	// 		Component->AddWorldRotation(NewRotation);
	// 	}
	// }
}

void UDoorOpener::GetDoorMeshComponent(TArray<UMeshComponent*>& OutMeshs) const
{
	TArray<UMeshComponent*> Components;
	this->GetOwner()->GetComponents<UMeshComponent>(Components);

	for(UMeshComponent* Component : Components)
	{
		if(Component->GetName() == LeftDoorName || Component->GetName() == RightDoorName)
		{
			OutMeshs.Add(Component);
		}
	}
}

void UDoorOpener::DoorOpen(bool isOpen)
{
	ShouldOpen = isOpen;

	//문 각도 이슈(트렐로 참고) 발생으로 임시 적용
	for(UMeshComponent* Component : Meshs)
	{
		if(Component->GetName() == LeftDoorName)
		{
			TargetRotation = OpenOffset;
		}
		else if(Component->GetName() == RightDoorName)
		{
			TargetRotation = OpenOffset * -1;
		}

		Component->AddWorldRotation(TargetRotation);
	}

	if(EnterTrigger != nullptr)
	{
		EnterTrigger->TriggerActivate();
	}
}

void UDoorOpener::SetEnterTrigger(UEnterTrigger* NewEnterTrigger)
{
	EnterTrigger = NewEnterTrigger;
}
