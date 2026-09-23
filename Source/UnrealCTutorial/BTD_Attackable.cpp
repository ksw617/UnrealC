// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_Attackable.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_Attackable::UBTD_Attackable()
{
	NodeName = TEXT("Attackable");
}

bool UBTD_Attackable::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//OwnerComponent를 통해 AIController가져와서 AIController 통해 Pawn 가져오기 
	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(Pawn))	// 값이 없음 false 리턴
		return false;

	//BlackboardComponent 가져와서 거기에 Object 타입에 키가 "Target" 애를 APawn으로 형변환 시도
	auto Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (!IsValid(Pawn)) //null이라면 false 리턴
		return false;

	//내 Pawn과 Target과의 거리가 300.f 벗어나면
	if (Target->GetDistanceTo(Pawn) > 300.f)
		return false; //false 리턴


	return Result;
}
