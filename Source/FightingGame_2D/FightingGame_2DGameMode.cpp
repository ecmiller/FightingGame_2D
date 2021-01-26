// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGame_2DGameMode.h"
#include "FightingGame_2DCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFightingGame_2DGameMode::AFightingGame_2DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
