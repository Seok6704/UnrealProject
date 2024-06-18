// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnterTrigger.h"
#include "TorchTimer.h"
#include "BoxTriggerComponent.h"
#include "Mover.h"
#include "Room1GameController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API URoom1GameController : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URoom1GameController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetEnterTrigger_Room1(UEnterTrigger* EnterTrigger);

	UFUNCTION(BlueprintCallable)
	void SetBoxTrigger(TArray<UBoxTriggerComponent*> BoxTrigger);

	UFUNCTION(BlueprintCallable)
	void SetTorch(TArray<UTorchTimer*> Torchs);

	UFUNCTION(BlueprintCallable)
	void SetPot(TArray<AActor*> Pots);

	UFUNCTION(BlueprintCallable)
	void SetMover_Room1(UMover* Mover);

private:
	UEnterTrigger* EnterTrigger;

	UMover* Mover;

	TArray<UBoxTriggerComponent*> BoxTrigger;

	bool isBegin = false;

	TArray<UTorchTimer*> Torchs;

	TArray<int32> QuestOrder;

	TArray<int32> AnswerOrder;

	void ShuffleOrder();

	void ShowQuestion();

	FTimerHandle QuestionTimerHandle;

	int32 TorchCount;

	UPROPERTY(EditAnywhere)
	float QuestionTime;

	void RunTorchTimer();

	int32 Start = 0;

	void AddAnswer();

	void ReturnPotPos();

	TArray<AActor*> Pots;

	TArray<FVector> OriginalPotPos;
};
