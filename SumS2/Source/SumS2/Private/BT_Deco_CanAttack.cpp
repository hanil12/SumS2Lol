// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_CanAttack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "MyPlayer.h"
#include "MyEnemy.h"

bool UBT_Deco_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if(result == false)
		return result;

	auto currentPawn = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	auto player = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Player"))));

	if(!currentPawn->IsValidLowLevel() || !player->IsValidLowLevel())
		return false;

	float distance = player->GetDistanceTo(currentPawn);
	if(distance < currentPawn->AttackRange())
		return true;

	return false;
}
