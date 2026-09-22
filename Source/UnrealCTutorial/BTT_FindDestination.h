// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_FindDestination.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCTUTORIAL_API UBTT_FindDestination : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_FindDestination();
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
