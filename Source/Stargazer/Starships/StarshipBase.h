// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ProjectileBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "StarshipBase.generated.h"

UCLASS()
class STARGAZER_API AStarshipBase : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent *SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent *StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UFloatingPawnMovement *FloatingMovement;

	bool isFiring;
	float fireRate;
	FTimerHandle ShootHandle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Starship|Prep")
		TSubclassOf<class AProjectileBase> ProjectileSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Starship|Prep")
		int32 shipHalfLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Starship|Gameplay")
		int32 shipHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Starship|Gameplay")
		int32 shipShields;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Starship|Gameplay")
		int32 shotsPerSecond;

	// Sets default values for this character's properties
	AStarshipBase(const FObjectInitializer& ObjectInitializer);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool ToggleShoot(bool status);
	virtual void Shoot();
};
