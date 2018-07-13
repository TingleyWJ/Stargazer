// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIStarshipControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class STARGAZER_API AAIStarshipControllerBase : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
		UBlackboardData *blackboardToUse;

	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
		UBehaviorTree *behaviorTreeToUse;

protected:
	virtual void BeginPlay() override;

public:
	AAIStarshipControllerBase();
};
