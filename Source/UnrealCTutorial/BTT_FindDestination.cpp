// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindDestination.h"
#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FindDestination::UBTT_FindDestination()
{
	NodeName = TEXT("Find Destination");
}

EBTNodeResult::Type UBTT_FindDestination::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();

	if (IsValid(Pawn))
	{
		auto NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (IsValid(NavSystem))
		{
			//위치 담을 구조체
			FNavLocation RandomLocation;

			//만약에 도달할 위치 값을 찾았다면
			//GetRandomReachablePointInRadius(중심점, 반지름, OUT 담을 위치)
			if (NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), 1000.f, OUT RandomLocation))
			{

				//OwnerComp.GetBlackboardComponent()->SetValueAsVector("블랙 보드 키 이름", 넣어줄 값)
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Destination"), RandomLocation);

				UE_LOG(LogTemp, Log, TEXT("Find Destination"));

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
