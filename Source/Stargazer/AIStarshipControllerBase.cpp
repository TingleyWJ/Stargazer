// Fill out your copyright notice in the Description page of Project Settings.

#include "AIStarshipControllerBase.h"

AAIStarshipControllerBase::AAIStarshipControllerBase()
{
	
}

void AAIStarshipControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Log, TEXT("BeginPlay Begin"));

	if (!ensure(blackboardToUse)) { return; }
	UseBlackboard(blackboardToUse, Blackboard);

	if (!ensure(behaviorTreeToUse)) { return; }

	RunBehaviorTree(behaviorTreeToUse);

	//UE_LOG(LogTemp, Log, TEXT("BeginPlay Complete"));
}