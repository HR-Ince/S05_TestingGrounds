// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingCharacter.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrollingPawn = Cast<APatrollingCharacter>(ControlledPawn);
	auto PatrolPoints = PatrollingPawn->PatrolPointsCPP;

	if(!PatrolPoints.Num()) { return EBTNodeResult::Succeeded; }

	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComponent->SetValueAsObject(NextWaypointKey.SelectedKeyName, PatrolPoints[Index]);
	
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}