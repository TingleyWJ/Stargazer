// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StarshipBase.generated.h"

UCLASS()
class STARGAZER_API AStarshipBase : public ACharacter
{
	GENERATED_BODY()

	float turnRate;
	float rollRate;
	bool isFiring;
	float fireRate;
	FTimerHandle ShootHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AProjectileBase> ProjectileSpawn;

	UPROPERTY(EditDefaultsOnly)
		int32 shipHalfLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 shotsPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 shipHealth;

	// Sets default values for this character's properties
	AStarshipBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Thrust(float value);
	void ThrustStrafe(float value);

	void Turn(float value);
	void LookUp(float value);
	
	void ToggleShoot();
	void Shoot();
};
