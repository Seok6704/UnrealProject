// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EnterTrigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UEnterTrigger : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	UEnterTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool isEnterPlayer() const;

	void TriggerActivate();

private:
	UPROPERTY(EditAnywhere)
	FName PlayerTag;

	bool isEnter;

	AActor* GetPlayer() const;
};
