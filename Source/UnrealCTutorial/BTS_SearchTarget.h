// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SearchTarget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCTUTORIAL_API UBTS_SearchTarget : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_SearchTarget();
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
