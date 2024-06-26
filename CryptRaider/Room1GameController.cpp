// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1GameController.h"

// Sets default values for this component's properties
URoom1GameController::URoom1GameController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
	// ...
}


// Called when the game starts
void URoom1GameController::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void URoom1GameController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(EnterTrigger->isEnterPlayer() && !isBegin) // 플레이어 입장
	{
		if(Torchs.Num() != 0) // 미션 횃불 존재 여부 체크
		{
			isBegin = true; // 게임 시작
			ShuffleOrder();
			ShowQuestion();
		}
		for(UBoxTriggerComponent* Trigger : BoxTrigger) // Box 트리거 활성화
		{
			Trigger->TriggerActivate();
		}
		for(AActor* Pot : Pots) // Pot 기본 위치 값 저장
		{
			OriginalPotPos.Add(Pot->GetActorLocation());
		}
	}

	if(isBegin && !isClear) AddAnswer();

	if(isClear)
	{
		if(!Room1KeyTrigger->isOnTrigger())
		{
			SetStandVisible();
			SetComponentTickEnabled(false); // Tick 사용 종료.
		}
	}
}

void URoom1GameController::SetEnterTrigger_Room1(UEnterTrigger* NewEnterTrigger) // EnterTrigger 연결
{
	EnterTrigger = NewEnterTrigger;
}

void URoom1GameController::SetBoxTrigger(TArray<UBoxTriggerComponent*> NewBoxTrigger) // BoxTrigger 연결
{
	for(UBoxTriggerComponent* Trigger : NewBoxTrigger)
	{
		BoxTrigger.Add(Trigger);
	}
}

void URoom1GameController::SetPot(TArray<AActor*> NewPots) // Pot 연결
{
	for(AActor* Pot : NewPots)
	{
		Pots.Add(Pot);
	}
}

void URoom1GameController::SetMover_Room1(UMover* NewMover)
{
	Mover = NewMover;
}

void URoom1GameController::SetDeathCount_Room1(UDeathCount* NewDeathCount)
{
	DeathCount = NewDeathCount;
}

void URoom1GameController::SetTorch(TArray<UTorchTimer*> NewTorchs) //Torch 연결
{
	for(UTorchTimer* Torch : NewTorchs)
	{
		Torchs.Add(Torch);
	}

	for(int32 i = 0; i < Torchs.Num(); i++) // 정답 숫자 배열 생성
	{
		QuestOrder.Add(i);
	}

	TorchCount = Torchs.Num(); // 횃불 숫자 기록
}

void URoom1GameController::SetGargoyleStand(TArray<AActor*> NewGargoyleStands) // Room1 클리어 후 생성되는 가고일 스탠드 연결
{
	for(AActor* GargoyleStand : NewGargoyleStands)
	{
		GargoyleStands.Add(GargoyleStand);
	}
}

void URoom1GameController::SetKeyBoxTrigger(UBoxTriggerComponent* NewRoom1KeyTrigger) // Room1 클리어 후 습득하는 가고일 스탠드 박스 트리거 연결
{
	Room1KeyTrigger = NewRoom1KeyTrigger;
}


void URoom1GameController::ShuffleOrder() // 정답 생성
{
	if(QuestOrder.Num() <= 0) return;

	for(int32 i = 0; i < QuestOrder.Num(); i++)
	{
		int32 Index = FMath::RandRange(i, QuestOrder.Num() - 1);
		if(i != Index) QuestOrder.Swap(i, Index);
	}
}

void URoom1GameController::ShowQuestion() // 문제 출제 시작
{
	GetWorld()->GetTimerManager().SetTimer(QuestionTimerHandle, this, &URoom1GameController::RunTorchTimer, QuestionTime, true);
}

void URoom1GameController::RunTorchTimer() // TorchTimer 작동
{
	Torchs[QuestOrder[Start]]->RunTimer();

	Start++;

	if(Start >= TorchCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(QuestionTimerHandle);
	}
}

void URoom1GameController::AddAnswer() // 답변 배열 생성
{
	if(AnswerOrder.Num() >= QuestOrder.Num()) // 답변 기록 완료
	{
		// Check Corret Answer

		if(AnswerOrder == QuestOrder) // 정답
		{
			UE_LOG(LogTemp, Display, TEXT("Correct!"));
			isClear = true; // 클리어 설정
			Room1KeyTrigger->TriggerActivate();
			Mover->OnMove();
		}
		else // 오답
		{
			UE_LOG(LogTemp, Display, TEXT("inCorrect"));
			DeathCount->Death();
			ReturnPotPos();
			AnswerOrder.Empty();
		}
	}
	else
	{
		for(int i = 0; i < BoxTrigger.Num(); i++)
		{
			if(BoxTrigger[i]->isOnTrigger() && !AnswerOrder.Contains(i))
			{
				AnswerOrder.Add(i);
			}
			else continue;
		}
	}
}

void URoom1GameController::ReturnPotPos() // Pot 원위치
{
	for(int32 i = 0; i < Pots.Num(); i++)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Pots[i]->GetRootComponent());
		if(Component != nullptr)
		{
			Component->SetSimulatePhysics(true);
		}
		Pots[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Pots[i]->SetActorLocation(OriginalPotPos[i]);
	}
}

void URoom1GameController::SetStandVisible() // Room1 가고일 스탠드 활성화
{
	for(AActor* GargoyleStand : GargoyleStands)
	{
		GargoyleStand->SetActorHiddenInGame(false);
	}
}



