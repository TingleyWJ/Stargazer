// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStarshipControllerBase.h"
#include "UObject/ConstructorHelpers.h"

APlayerStarshipControllerBase::APlayerStarshipControllerBase()
{
	static ConstructorHelpers::FClassFinder<APlayerCameraManager> CamManager(TEXT("/Game/Blueprints/Player/StarshipCameraManager"));
	PlayerCameraManagerClass = CamManager.Class;

	/*if (PlayerCameraManager != NULL)
	{
		PlayerCameraManager->ViewPitchMin = -179.9999f;
		PlayerCameraManager->ViewPitchMax = 179.9999f;
	}*/
}

void APlayerStarshipControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Log, TEXT("BeginPlay Call???"));

	if (!ensure(OverlayType)) { return; }

	//UE_LOG(LogTemp, Log, TEXT("Test"));

	Overlay = CreateWidget<UUserWidget>(this, OverlayType);
	Overlay->AddToViewport();
	//bShowMouseCursor = true;
}