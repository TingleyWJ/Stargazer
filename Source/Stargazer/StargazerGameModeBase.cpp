// Fill out your copyright notice in the Description page of Project Settings.

#include "StargazerGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AStargazerGameModeBase::AStargazerGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PCharacterClass(TEXT("/Game/Blueprints/Player/Player"));
	static ConstructorHelpers::FClassFinder<AController> PControllerClass(TEXT("/Game/Blueprints/Player/PlayerStarshipController"));

	if (PCharacterClass.Class != NULL)
	{
		DefaultPawnClass = PCharacterClass.Class;
	}

	if (PControllerClass.Class != NULL)
	{
		PlayerControllerClass = PControllerClass.Class;
	}
}