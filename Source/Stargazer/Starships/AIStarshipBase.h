// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StarshipBase.h"
#include "AIStarshipBase.generated.h"

UCLASS()
class STARGAZER_API AAIStarshipBase : public AStarshipBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent *WidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	// Sets default values for this pawn's properties
	AAIStarshipBase(const FObjectInitializer &objectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Test: Toggles the AI's firing state. Result is true if the firing state was switched.
	UFUNCTION(BlueprintCallable, Category = "Gameplay", meta=(Tooltip="Toggles the AI's firing state. Result is true if the firing state was switched."))
	virtual bool ToggleShoot(bool status) override;

	virtual void Shoot() override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ModifyValues(int32 healthChange, int32 shieldChange);
};
