// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMyAIController::AMyAIController()
{
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 3초마다 RandMove함수 반복적으로 호출
	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &AMyAIController::RandMove, 3.0f, true);
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void AMyAIController::RandMove()
{
	auto curPawn = GetPawn(); // 현재 빙의되어있는 폰

	if(curPawn->IsValidLowLevel() == false)
		return;

	// 현재 설정한 NavMesh를 갖고 오는 것
	auto navMesh = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (navMesh->IsValidLowLevel() == false)
		return;

	// 랜덤한 위치...=> navMesh 물어보기
	FNavLocation randLocation;
	FVector pawnLocation = curPawn->GetActorLocation();

	if (navMesh->GetRandomPointInNavigableRadius(pawnLocation, 300.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation.Location);
	}
}
