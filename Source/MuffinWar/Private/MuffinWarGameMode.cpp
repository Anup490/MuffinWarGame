// Copyright Epic Games, Inc. All Rights Reserved.

#include "MuffinWarGameMode.h"
#include "MuffinWarCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMuffinWarGameMode::AMuffinWarGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
