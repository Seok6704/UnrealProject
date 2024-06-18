// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnterTrigger.h"
#include "DoorOpener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DoorOpen(bool isOpen);
	
	UFUNCTION(BlueprintCallable)
	void SetEnterTrigger(UEnterTrigger* EnterTrigger);

private:

	UPROPERTY(EditAnywhere)
	FRotator OpenOffset = FRotator(0, 80, 0);

	UPROPERTY(EditAnywhere)
	float OpenTime = 5000;

	UPROPERTY(EditAnywhere)
	FName RightDoorName = "SM_DoorWay_Large_Door_Right";

	UPROPERTY(EditAnywhere)
	FName LeftDoorName = "SM_DoorWay_Large_Door_Left";

	TArray<UMeshComponent*> Meshs;

	FRotator TargetRotation;

	bool ShouldOpen;

	void GetDoorMeshComponent(TArray<UMeshComponent*>& OutMeshs) const;

	UEnterTrigger* EnterTrigger;
};
