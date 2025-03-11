// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_Attack.h"

#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include <Kismet/KismetMathLibrary.h>

#include "MyEnemy.h"
#include "MyPlayer.h"

EBTNodeResult::Type UBT_Task_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto btNodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto currentPawn = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (currentPawn->IsValidLowLevel() == false)
		return btNodeResult;

	if(currentPawn->IsAttacking())
		return btNodeResult;

	auto player = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	if(!player->IsValidLowLevel())
		return EBTNodeResult::Failed;
	
	currentPawn->Attack_AI();

	return EBTNodeResult::Succeeded;
}
