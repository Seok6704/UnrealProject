// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"
#include "TorchTimer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTorchTimer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTorchTimer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RunTimer();

private:

	UPROPERTY(EditAnywhere)
	float TorchLife; // 횃불 수명(유지 시간)

	UPROPERTY(EditAnywhere)
	float CountTime; // 횃불 수명 감소 간격

	UPROPERTY(EditAnywhere)
	float StartIntensity; // 횃불 시작 밝기

	UPROPERTY(EditAnywhere)
	float DecreaseValue; // 횃불 밝기 감소치

	FTimerHandle CountdownTimerHandle;

	void DecreaseLight(); // 횃불 밝기 감소 함수

	UPointLightComponent* Light; // 포인트 라이트 변수

	bool isDead = false; // 다 꺼진 횃불 함수 실행 방지
	
	void TorchDead(); // 횃불 수명 종료 함수
};
