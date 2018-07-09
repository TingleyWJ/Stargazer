// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class STARGAZER_API AEnemyControllerBase : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
		UBlackboardData *blackboardToUse;

	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
		UBehaviorTree* BehaviorTreeToUse;

	//UPROPERTY()
		//UBlackboardComponent* test;

protected:
	virtual void BeginPlay() override;

public:
	AEnemyControllerBase();
};
