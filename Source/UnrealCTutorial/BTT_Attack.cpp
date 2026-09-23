// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"

UBTT_Attack::UBTT_Attack()
{
	NodeName = TEXT("Attack");

	//Tick È°¼ºÈ­
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UE_LOG(LogTemp, Log, TEXT("Attack"));

	return Result;
}

void UBTT_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
