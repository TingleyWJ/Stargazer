// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class STARGAZER_API AProjectileBase : public AActor
{
	GENERATED_BODY()

	int32 bulletSpeed;
	FTimerHandle DestroyHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector damage;

	// Sets default values for this actor's properties
	AProjectileBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RemoveWhenDone();
	
};
