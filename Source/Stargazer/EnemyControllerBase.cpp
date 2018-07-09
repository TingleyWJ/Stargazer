// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyControllerBase.h"

AEnemyControllerBase::AEnemyControllerBase()
{

}

void AEnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(blackboardToUse)) { return; }
	UseBlackboard(blackboardToUse, Blackboard);

	if (!ensure(BehaviorTreeToUse)) { return; }

	RunBehaviorTree(BehaviorTreeToUse);
}