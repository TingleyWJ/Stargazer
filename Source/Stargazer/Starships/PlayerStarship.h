// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StarshipBase.h"
#include "PlayerStarship.generated.h"

/**
 * 
 */
UCLASS()
class STARGAZER_API APlayerStarship : public AStarshipBase
{
	GENERATED_BODY()
	
	float turnRate;
	float rollRate;

	float strafeVal;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	APlayerStarship(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Thrust(float value);
	void ThrustStrafe(float value);

	void Turn(float value);
	void LookUp(float value);

	void ToggleShoot();
	virtual bool ToggleShoot(bool status) override;
	virtual void Shoot() override;
};
