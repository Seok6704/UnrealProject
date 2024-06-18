// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DoorOpener.h"
#include "Interaction.generated.h"

// 상호작용 구현 클래스(E 키 사용 시, 상호 작용 진행)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UInteraction : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool isInteract() const; // 상호작용 가능한지 확인

	void OnInteraction(); // 상호 작용 진행

private:

	float InteractDistance = 100; // 상호작용 거리

	float InteractRadius = 50;

	bool NowInteract = false; // 현재 상호작용 가능 확인 변수

	FHitResult HitResult;

	UDoorOpener* Opener;

	TMap<FName, int32> InterKeyMap;

	bool GetInteractInReach(FHitResult& OutHitResult) const;

	void InitMap();

	void SetOpener(UDoorOpener* Opener);
};
