// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StarshipCameraManagerBase.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStarshipControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class STARGAZER_API APlayerStarshipControllerBase : public APlayerController
{
	GENERATED_BODY()

	UUserWidget *Overlay;
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> OverlayType;

	APlayerStarshipControllerBase();
};
