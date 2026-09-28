// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"
#include "AIController.h"
#include "Enemy.h"

UBTT_Attack::UBTT_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (!IsValid(Enemy))
		return EBTNodeResult::Failed;

	if (!Enemy->IsAttack())
	{
		Enemy->EnemyAttack();
	}
	return Result;
}

void UBTT_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Enemy))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!Enemy->IsAttack())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
