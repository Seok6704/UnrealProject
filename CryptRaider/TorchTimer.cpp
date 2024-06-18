// Fill out your copyright notice in the Description page of Project Settings.


#include "TorchTimer.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UTorchTimer::UTorchTimer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // 틱 컴포넌트 사용 X

	// ...
}


// Called when the game starts
void UTorchTimer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Light = GetOwner()->FindComponentByClass<UPointLightComponent>();
	Light->SetIntensity(StartIntensity);
}


// Called every frame
void UTorchTimer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTorchTimer::RunTimer() // 타이머 시작
{
	if(isDead) return;
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UTorchTimer::DecreaseLight, CountTime, true);
}

void UTorchTimer::DecreaseLight() // 횃불 밝기 감소
{
	TorchLife -= CountTime;

	StartIntensity -= DecreaseValue;

	Light->SetIntensity(StartIntensity);
	
	if(TorchLife < 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		TorchDead();
	}
}

void UTorchTimer::TorchDead() // 횃불 수명 종료
{
	isDead = true;
	GetOwner()->FindComponentByClass<UParticleSystemComponent>()->SetActive(false);
}
