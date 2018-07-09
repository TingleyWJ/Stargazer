// Fill out your copyright notice in the Description page of Project Settings.

#include "StarshipController.h"
#include "UObject/ConstructorHelpers.h"

AStarshipController::AStarshipController()
{
	static ConstructorHelpers::FClassFinder<APlayerCameraManager> CamManager(TEXT("/Game/Blueprints/StarshipCameraManager"));
	PlayerCameraManagerClass = CamManager.Class;

	/*if (PlayerCameraManager != NULL)
	{
		PlayerCameraManager->ViewPitchMin = -179.9999f;
		PlayerCameraManager->ViewPitchMax = 179.9999f;
	}*/
}