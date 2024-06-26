// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathCount.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDeathCount::UDeathCount()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // 틱 사용 X

	// ...
}


// Called when the game starts
void UDeathCount::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetDeathCount();
}


// Called every frame
void UDeathCount::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDeathCount::SetDeathCount()
{
	GetOwner()->GetComponents<UStaticMeshComponent>(DeathCounts);

	DeathCounts.Sort();

	int32 NowDeathCounts = DeathCounts.Num();

	for(int32 i = NowDeathCounts - 1; i >= TotalDeathCount; i--)
	{
		DeathCounts[i]->DestroyComponent();
		DeathCounts.RemoveAt(i);
	}
}

void UDeathCount::Death()
{
	if(DeathCounts.Num() <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Dead!"));
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		return;
	}

	DeathCounts[DeathCounts.Num()-1]->DestroyComponent();
	DeathCounts.RemoveAt(DeathCounts.Num()-1);
}

