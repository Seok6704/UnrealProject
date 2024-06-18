// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	TargetLocation = GetOwner()->GetActorLocation() + MoveOffset;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMover::OnMove()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &UMover::MovePos, MoveInterval, true);
}

void UMover::MovePos()
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	if(CurrentLocation == TargetLocation)
	{
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
	}
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, MoveInterval, Speed);
	
	GetOwner()-> SetActorLocation(NewLocation);

}

