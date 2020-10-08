// Copyright Epic Games, Inc. All Rights Reserved.

#include "MuffinWarGameMode.h"
#include "MuffinWarCharacter.h"
#include "MuffinWarGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AMuffinWarGameMode::AMuffinWarGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	bIsGamePaused = false;
}

bool AMuffinWarGameMode::IsGamePaused()
{
	return bIsGamePaused;
}

void AMuffinWarGameMode::StartPlay()
{
	Super::StartPlay();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	FInputModeGameOnly InputMode;
	Controller->SetInputMode(InputMode);	
}