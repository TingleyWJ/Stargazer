// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "StarshipCameraManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class STARGAZER_API AStarshipCameraManagerBase : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AStarshipCameraManagerBase();
};
