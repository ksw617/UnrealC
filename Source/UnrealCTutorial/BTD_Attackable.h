// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_Attackable.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCTUTORIAL_API UBTD_Attackable : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTD_Attackable();
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
